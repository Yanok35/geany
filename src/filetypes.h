/*
 *      filetypes.h - this file is part of Geany, a fast and lightweight IDE
 *
 *      Copyright 2005-2008 Enrico Tröger <enrico(dot)troeger(at)uvena(dot)de>
 *      Copyright 2006-2008 Nick Treleaven <nick(dot)treleaven(at)btinternet(dot)com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $Id$
 */


#ifndef GEANY_FILETYPES_H
#define GEANY_FILETYPES_H 1

#include "Scintilla.h"
#include "ScintillaWidget.h"


/* Each group should be alpha-sorted, based on filetype::name (not enum name).
 * Warning: remember to break the plugin ABI when adding items (this enum needs to be changed
 * to work with an ABI-stable filetype::group_name field. */
typedef enum
{
	/* normally compiled languages */
	GEANY_FILETYPES_GROUP_COMPILED = 0,
	GEANY_FILETYPES_ASM = GEANY_FILETYPES_GROUP_COMPILED,
	GEANY_FILETYPES_C,
	GEANY_FILETYPES_CPP,
	GEANY_FILETYPES_CS,
	GEANY_FILETYPES_CAML,
	GEANY_FILETYPES_D,
	GEANY_FILETYPES_F77,
	GEANY_FILETYPES_FORTRAN,
	GEANY_FILETYPES_BASIC,	/* FreeBasic */
	GEANY_FILETYPES_HASKELL,
	GEANY_FILETYPES_HAXE,
	GEANY_FILETYPES_JAVA,
	GEANY_FILETYPES_PASCAL,
	GEANY_FILETYPES_VHDL,

	/* script languages */
	GEANY_FILETYPES_GROUP_SCRIPT,
	GEANY_FILETYPES_FERITE = GEANY_FILETYPES_GROUP_SCRIPT,
	GEANY_FILETYPES_JS,
	GEANY_FILETYPES_LUA,
	GEANY_FILETYPES_MAKE,
	GEANY_FILETYPES_OMS,
	GEANY_FILETYPES_PERL,
	GEANY_FILETYPES_PHP,
	GEANY_FILETYPES_PYTHON,
	GEANY_FILETYPES_RUBY,
	GEANY_FILETYPES_SH,
	GEANY_FILETYPES_TCL,

 	/* markup langauges */
	GEANY_FILETYPES_GROUP_MARKUP,
	GEANY_FILETYPES_CSS = GEANY_FILETYPES_GROUP_MARKUP,
	GEANY_FILETYPES_DOCBOOK,
	GEANY_FILETYPES_HTML,
 	GEANY_FILETYPES_XML,

	/* miscellaneous languages */
	GEANY_FILETYPES_GROUP_MISC,
	GEANY_FILETYPES_CONF = GEANY_FILETYPES_GROUP_MISC,
	GEANY_FILETYPES_DIFF,
	GEANY_FILETYPES_LATEX,
	GEANY_FILETYPES_REST,
	GEANY_FILETYPES_SQL,

	GEANY_FILETYPES_NONE,	/* must be last filetype */
	GEANY_MAX_BUILT_IN_FILETYPES	/* Use filetypes_array->len instead */
} filetype_id;

/* Safe wrapper to get the id field of a possibly NULL filetype pointer. */
#define FILETYPE_ID(filetype_ptr) \
	(((filetype_ptr) != NULL) ? (filetype_ptr)->id : GEANY_FILETYPES_NONE)


struct build_actions
{
	gboolean	can_compile;
	gboolean	can_link;
	gboolean	can_exec;
};

struct build_programs
{
	gchar *compiler;
	gchar *linker;
	gchar *run_cmd;
	gchar *run_cmd2;
	gboolean modified;
};

/** Represents a filetype. */
struct GeanyFiletype
{
	filetype_id		  id;				/**< Index in @c filetypes_array. */
	/** Represents the langType of tagmanager (see the table
	 * in tagmanager/parsers.h), -1 represents all, -2 none. */
	langType 		  lang;
	gchar	 		 *name;				/**< Used as name for tagmanager. E.g. "C". */
	gchar	 		 *title;			/**< Shown in the file open dialog. E.g. "C source file". */
	gchar	 		 *extension;		/**< Default file extension for new files. */
	gchar			**pattern;			/**< Array of filename-matching wildcard strings. */
	gchar	 		 *context_action_cmd;
	gchar	 		 *comment_open;
	gchar	 		 *comment_close;
	gboolean  		  comment_use_indent;
	struct build_programs	*programs;
	struct build_actions	*actions;
};

extern GPtrArray *filetypes_array;

/* Wrap filetypes_array so it can be used with C array syntax.
 * Example: filetypes[GEANY_FILETYPES_C]->name = ...; */
#define filetypes	((GeanyFiletype **)filetypes_array->pdata)


GeanyFiletype *filetypes_lookup_by_name(const gchar *name);


void filetypes_init(void);

void filetypes_init_types(void);

GeanyFiletype *filetypes_detect_from_document(GeanyDocument *doc);

GeanyFiletype *filetypes_detect_from_extension(const gchar *utf8_filename);

GeanyFiletype *filetypes_detect_from_file(const gchar *utf8_filename);

void filetypes_free_types(void);

void filetypes_load_config(gint ft_id, gboolean reload);

void filetypes_save_commands(void);

void filetypes_select_radio_item(const GeanyFiletype *ft);

GtkFileFilter *filetypes_create_file_filter(const GeanyFiletype *ft);

GtkFileFilter *filetypes_create_file_filter_all_source(void);

gchar *filetypes_get_conf_extension(gint filetype_idx);

gboolean filetype_has_tags(GeanyFiletype *ft);

#endif
