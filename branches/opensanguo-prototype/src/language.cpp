/* $Id: language.cpp 39290 2009-10-14 21:09:47Z loonycyborg $ */
/*
   Copyright (C) 2003 - 2009 by David White <dave@whitevine.net>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#include "global.hpp"

#include "filesystem.hpp"
#include "foreach.hpp"
#include "gettext.hpp"
#include "language.hpp"
#include "log.hpp"
#include "preferences.hpp"
#include "serialization/parser.hpp"
#include "serialization/preprocessor.hpp"

#include <stdexcept>
#include <clocale>
#include <boost/scoped_array.hpp>

#ifdef _WIN32
#include <windows.h>
#ifndef _MSC_VER
extern "C" int _putenv(const char*);
#endif
#endif

#ifdef __APPLE__
#include <cerrno>
#endif

#define DBG_G LOG_STREAM(debug, lg::general)
#define LOG_G LOG_STREAM(info, lg::general)
#define WRN_G LOG_STREAM(warn, lg::general)
#define ERR_G LOG_STREAM(err, lg::general)


/** Tests one locale to be available. */
static bool has_locale(const char* s) {
	try {
		// The way to find out whether a locale is available is to set it and
		// hope not runtime error gets thrown.
		std::locale dummy(s);
		return true;
	} catch (std::runtime_error&) {
		return false;
	}
}

/** Test the locale for a language and it's utf-8 variations. */
static bool has_language(const std::string& language)
{
	if(has_locale(language.c_str())) {
		return true;
	}

	std::string utf = language + ".utf-8";
	if(has_locale(utf.c_str())) {
		return true;
	}

	utf = language + ".UTF-8";
	if(has_locale(utf.c_str())) {
		return true;
	}

	return false;
}

namespace {
	language_def current_language;
	string_map strings_;
}

static language_list known_languages;

bool current_language_rtl()
{
	return get_language().rtl;
}

bool language_def::operator== (const language_def& a) const
{
	return ((language == a.language) /* && (localename == a.localename) */ );
}

bool language_def::available() const
{
#if defined(_WIN32) || defined(__APPLE__)
	// Under windows and OSX all locales are available and testing for it seems
	// to fail so just return true.
	return true;
#endif

	//if (game_config::use_dummylocales)
	if (true)
	{
		// Dummy has every language available.
		return true;
	} else {
		if(has_language(localename)) {
			return true;
		} else {
			foreach(const std::string& lang, alternates) {
				if(has_language(lang)) {
					return true;
				}
			}
		}

		return false;
	}
}

symbol_table string_table;

const t_string& symbol_table::operator[](const std::string& key) const
{
	const string_map::const_iterator i = strings_.find(key);
	if(i != strings_.end()) {
		return i->second;
	} else {
		static t_string empty_string;
		// Let's do it the painful way (untlb means untranslatABLE).
		// It will cause problem if somebody stores more than one reference at once
		// but I don't really care since this path is an error path and it should
		// not have been taken in the first place. -- silene
		empty_string = "UNTLB " + key;
		return empty_string;
	}
}

const t_string& symbol_table::operator[](const char* key) const
{
	return (*this)[std::string(key)];
}

bool load_language_list()
{
	config cfg;
	try {
		scoped_istream stream = preprocess_file(get_wml_location("hardwired/language.cfg"));
		read(cfg, *stream);
	} catch(config::error &) {
		return false;
	}

	known_languages.clear();
	known_languages.push_back(
		language_def("", t_string(N_("System default language"), "wesnoth"), "ltr", "", "A"));

	foreach (const config &lang, cfg.child_range("locale"))
	{
		known_languages.push_back(
			language_def(lang["locale"], lang["name"], lang["dir"],
			             lang["alternates"], lang["sort_name"]));
	}

	return true;
}

language_list get_languages()
{
	// We sort every time, the local might have changed which can modify the
	// sort order.
	std::sort(known_languages.begin(), known_languages.end());
	return known_languages;
}

static void wesnoth_setlocale(int category, std::string const &slocale,
	std::vector<std::string> const *alternates)
{
	std::string locale = slocale;
	// FIXME: ideally we should check LANGUAGE and on first invocation
	// use that value, so someone with es would get the game in Spanish
	// instead of en_US the first time round
	// LANGUAGE overrides other settings, so for now just get rid of it
	// FIXME: add configure check for unsetenv
#ifndef _WIN32
#ifndef __AMIGAOS4__
	unsetenv ("LANGUAGE"); // void so no return value to check
#endif
#endif

#if defined(__BEOS__) || defined(__APPLE__)
	if (category == LC_MESSAGES && setenv("LANG", locale.c_str(), 1) == -1)
		ERR_G << "setenv LANG failed: " << strerror(errno);
#endif

#ifdef _WIN32
	std::string win_locale(locale, 0, 2);
	#include "language_win32.ii"
	if(category == LC_MESSAGES) {
		std::string env = "LANG=" + locale;
		_putenv(env.c_str());
		SetEnvironmentVariable("LANG", win_locale.c_str());
		return;
	}
	locale = win_locale;
#endif

	std::string extra;

#ifdef USE_DUMMYLOCALES
	if (game_config::use_dummylocales)
	{
		static enum { UNINIT, NONE, PRESENT } status = UNINIT;
		static std::string locpath;
		if (status == UNINIT) {
			if (char const *p = getenv("LOCPATH")) {
				locpath = p;
				status = PRESENT;
			} else status = NONE;
		}
		if (locale.empty())
			if (status == NONE)
				unsetenv("LOCPATH");
			else
				setenv("LOCPATH", locpath.c_str(), 1);
		else {
			std::string path = game_config::path + "/locales";
			setenv("LOCPATH", path.c_str(), 1);
			DBG_G << "LOCPATH set to '" << path << "'\n";
		}
		std::string xlocale;
		if (!locale.empty()) {
			// dummy suffix to prevent locale aliasing from kicking in
			extra = "@wesnoth";
			xlocale = locale + "@wesnoth";
			locale = xlocale.c_str();
		}
	}
#endif

	char *res = NULL;
	std::vector<std::string>::const_iterator i;
	if (alternates) i = alternates->begin();

	for (;;)
	{
		res = std::setlocale(category, locale.c_str());
		if (res) break;

		std::string utf8 = locale + ".utf-8";
		res = std::setlocale(category, utf8.c_str());
		if (res) break;

		utf8 = locale + ".UTF-8";
		res = std::setlocale(category, utf8.c_str());
		if (res) break;

		if (!alternates || i == alternates->end()) break;
		locale = *i + extra;
		++i;
	}

	if (res)
		LOG_G << "Set locale to '" << locale << "' result: '" << res <<"'.\n";
	else {
		WRN_G << "setlocale() failed for '" << slocale << "'.\n";
#ifndef _WIN32
#ifndef __AMIGAOS4__
		if(category == LC_MESSAGES) {
			WRN_G << "Setting LANGUAGE to '" << slocale << "'.\n";
			setenv("LANGUAGE", slocale.c_str(), 1);
			std::setlocale(LC_MESSAGES, "");
		}
#endif
#endif
	}

	DBG_G << "Numeric locale: " << std::setlocale(LC_NUMERIC, NULL) << '\n';
	DBG_G << "Full locale: " << std::setlocale(LC_ALL, NULL) << '\n';
}

bool set_language(const language_def& locale)
{
	strings_.clear();

	std::string locale_lc;
	locale_lc.resize(locale.localename.size());
	std::transform(locale.localename.begin(),locale.localename.end(),locale_lc.begin(),tolower);

	config cfg;

	current_language = locale;
	wesnoth_setlocale(LC_COLLATE, locale.localename, &locale.alternates);
	wesnoth_setlocale(LC_TIME, locale.localename, &locale.alternates);
	wesnoth_setlocale(LC_MESSAGES, locale.localename, &locale.alternates);

	// fill string_table (should be moved somwhere else some day)
	try {
		scoped_istream stream = preprocess_file(get_wml_location("hardwired/english.cfg"));
		read(cfg, *stream);
	} catch(config::error& e) {
		std::cerr << "Could not read english.cfg\n";
		throw e;
	}

	config &langp = cfg.child("language");
	if (!langp) {
		std::cerr << "No [language] block found in english.cfg\n";
		return false;
	}

	foreach (const config::attribute &j, langp.attribute_range()) {
		strings_[j.first] = j.second;
	}
	// end of string_table fill

	return true;
}

const language_def& get_language() { return current_language; }

const language_def& get_locale()
{
	//TODO: Add in support for querying the locale on Windows

	assert(known_languages.size() != 0);

	const std::string& prefs_locale = preferences::language();
	if(prefs_locale.empty() == false) {
		wesnoth_setlocale(LC_MESSAGES, prefs_locale, NULL);
		for(language_list::const_iterator i = known_languages.begin();
				i != known_languages.end(); ++i) {
			if (prefs_locale == i->localename)
				return *i;
		}
		LOG_G << "'" << prefs_locale << "' locale not found in known array; defaulting to system locale\n";
		return known_languages[0];
	}

#if 0
	const char* const locale = getenv("LANG");
	#ifdef _WIN32
	    std::string win_locale = locale
		#include "language_win32.ii"
		return win_locale;
	#endif
	if(locale != NULL && strlen(locale) >= 2) {
		//we can't pass pointers into the string to the std::string
		//constructor because some STL implementations don't support
		//it (*cough* MSVC++6)
		std::string res(2,'z');
		res[0] = tolower(locale[0]);
		res[1] = tolower(locale[1]);
		return res;
	}
#endif

	LOG_G << "locale could not be determined; defaulting to system locale\n";
	return known_languages[0];
}

void init_textdomains(const config& cfg)
{
	foreach (const config &t, cfg.child_range("textdomain"))
	{
		const std::string &name = t["name"];
		const std::string &path = t["path"];

		if(path.empty()) {
			t_string::add_textdomain(name, get_intl_dir());
		} else {
			std::string location = get_binary_dir_location("", path);

			if (location.empty()) {
				//if location is empty, this causes a crash on Windows, so we
				//disallow adding empty domains
				ERR_G << "no location found for '" << path << "', skipping textdomain\n";
			} else {
				t_string::add_textdomain(name, location);
			}
		}
	}
}

/* vim:set encoding=utf-8: */
