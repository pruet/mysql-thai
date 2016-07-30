/* Copyright (c) 2005, 2016, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA */

// First include (the generated) my_config.h, to get correct platform defines.
#include "my_config.h"
#include <my_sys.h>
#include <mysql/plugin_ftparser.h>
/*#include <my_global.h>
#include <m_ctype.h>
#include <my_list.h>
#include <mysql_version.h>
#include <plugin.h>*/

#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#if !defined(__attribute__) && (defined(__cplusplus) || !defined(__GNUC__)  || __GNUC__ == 2 && __GNUC_MINOR__ < 8)
#define __attribute__(A)
#endif

#ifdef HAVE_CHARSET_ucs2
extern CHARSET_INFO my_charset_ucs2_thai_520_w2;
#endif

#ifdef HAVE_CHARSET_utf8
extern CHARSET_INFO my_charset_utf8_thai_520_w2;
#endif

/*
  Initialize the parser plugin at server start or plugin installation.

  SYNOPSIS
    mysql_thai_plugin_init()

  DESCRIPTION
    Does nothing.

  RETURN VALUE
    0                    success
    1                    failure (cannot happen)
*/

static int mysql_thai_plugin_init(void *arg MY_ATTRIBUTE((unused)))
{
  int i= 0;
  int lastUtf8 = 0;
  int lastUcs2 = 0;

  for (i= 0; i < sizeof(all_charsets) / sizeof(all_charsets[0]); i++ ) {
    if (all_charsets[i])
    {
      if (strcmp(all_charsets[i]->csname, "utf8") == 0) lastUtf8= i;
      if (strcmp(all_charsets[i]->csname, "ucs2") == 0) lastUcs2= i;
    }
  }

#ifdef HAVE_CHARSET_ucs2
  my_charset_ucs2_thai_520_w2.number = lastUcs2 + 1;
  all_charsets[lastUcs2 + 1] = &my_charset_ucs2_thai_520_w2;
  all_charsets[lastUcs2 + 1]->state |= MY_CS_AVAILABLE;
#endif
#ifdef HAVE_CHARSET_utf8
  my_charset_utf8_thai_520_w2.number = lastUtf8 + 1;
  all_charsets[lastUtf8 + 1] = &my_charset_utf8_thai_520_w2;
  all_charsets[lastUtf8 + 1]->state |= MY_CS_AVAILABLE;
#endif
}


/*
  Terminate the parser plugin at server shutdown or plugin deinstallation.

  SYNOPSIS
    mysql_thai_plugin_deinit()
    Does nothing.

  RETURN VALUE
    0                    success
    1                    failure (cannot happen)

*/

static int mysql_thai_plugin_deinit(void *arg MY_ATTRIBUTE((unused)))
{
  /* TODO: remove the charsets data */
  return(0);
}


/*
  Initialize the parser on the first use in the query

  SYNOPSIS
    mysql_thai_init()

  DESCRIPTION
    Does nothing.

  RETURN VALUE
    0                    success
    1                    failure (cannot happen)
*/

static int mysql_thai_init(MYSQL_FTPARSER_PARAM *param
                              MY_ATTRIBUTE((unused)))
{
  return(0);
}


/*
  Terminate the parser at the end of the query

  SYNOPSIS
    mysql_thai_deinit()

  DESCRIPTION
    Does nothing.

  RETURN VALUE
    0                    success
    1                    failure (cannot happen)
*/

static int mysql_thai_deinit(MYSQL_FTPARSER_PARAM *param
                                MY_ATTRIBUTE((unused)))
{
  return(0);
}

/*
  Parse a document or a search query.

  SYNOPSIS
    mysql_thai_parse()
      param              parsing context

  DESCRIPTION
    This is the main plugin function which is called to parse
    a document or a search query. The call mode is set in
    param->mode.  This function simply splits the text into words
    and passes every word to the MySQL full-text indexing engine.

  RETURN VALUE
    0                    success
    1                    failure (cannot happen)
*/

static int mysql_thai_parse(MYSQL_FTPARSER_PARAM *param)
{
  return(0);
}


/*
  Plugin type-specific descriptor
*/

static struct st_mysql_ftparser mysql_thai_descriptor=
{
  MYSQL_FTPARSER_INTERFACE_VERSION, /* interface version      */
  mysql_thai_parse,              /* parsing function       */
  mysql_thai_init,               /* parser init function   */
  mysql_thai_deinit              /* parser deinit function */
};

/*
  Plugin library descriptor
*/

mysql_declare_plugin(mysql_thai)
{
  MYSQL_FTPARSER_PLUGIN,      /* type                            */
  &mysql_thai_descriptor,  /* descriptor                      */
  "mysql_thai",            /* name                            */
  "Pruet Boonma <pruet@eng.cmu.ac.th>",              /* author                          */
  "UTF-8 Thai Collation Plugin",  /* description                     */
  PLUGIN_LICENSE_GPL,
  mysql_thai_plugin_init,  /* init function (when loaded)     */
  mysql_thai_plugin_deinit,/* deinit function (when unloaded) */
  0x0001,                     /* version                         */
  NULL,              /* status variables                */
  NULL,    /* system variables                */
  NULL
}
mysql_declare_plugin_end;

