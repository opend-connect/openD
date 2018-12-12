// =============================================================================
/*!
 * @file       apps/common.cpp
 *
 * This file contains the implementation of the common functionality for the
 * HAN-FUN example application.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 ULE Alliance
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 *
 * Initial development by Bithium S.A. [http://www.bithium.com]
 */
// =============================================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

#include <cstdint>

#include "common.h"
#include "application.h"

/*!
 * @addtogroup examples
 */

// =============================================================================
// Commands API
// =============================================================================

std::map <std::string, ICommand *> ICommand::registry;

// =============================================================================
// ICommand::add
// =============================================================================
/*!
 *
 */
// =============================================================================
void ICommand::add (ICommand *command)
{
   registry.insert (std::pair <std::string, ICommand *>(command->key (), command));
}

// =============================================================================
// ICommand::remove
// =============================================================================
/*!
 *
 */
// =============================================================================
void ICommand::remove (ICommand *command)
{
   registry.erase (command->key ());
}

// =============================================================================
// ICommand::help
// =============================================================================
/*!
 *
 */
// =============================================================================
std::ostream &ICommand::help (std::ostream &_stream)
{
   struct entry
   {
      std::string cmd;
      std::string help;
   };

   static std::string cache   = "";
   static uint8_t cache_count = 0;

   if (cache_count == ICommand::registry.size())
   {
      _stream << cache;
      return _stream;
   }

   std::stringstream stream;

   uint16_t size = 0;
   std::vector <entry> entries;

   /* *INDENT-OFF* */
   std::for_each (ICommand::registry.begin (), ICommand::registry.end (),
                  [&entries, &size](std::pair <std::string, ICommand *> e)
   {
      // LOG (TRACE) << "E F : " << e.first << NL;
      // LOG (TRACE) << "E S : " << e.second << NL;

      const std::string &raw = e.second->usage ();

      char *temp = new char[raw.size ()+1];

      strncpy (temp, raw.c_str (), raw.size ())[raw.size ()] = 0;

      std::vector <char *> lines;

      char *saveptr = NULL;
      for (char *p = strtok_r (temp, "\n", &saveptr); p != NULL; p = strtok_r (NULL, "\n", &saveptr))
      {
         lines.push_back (p);
      }

      std::for_each (lines.begin (), lines.end (), [&entries, &size](char *line)
      {
         entry e;

         char *saveptr = NULL;
         char *p = strtok_r (line, ":", &saveptr);
         e.cmd = std::string (p);

         p = strtok_r (NULL, ":", &saveptr);
         e.help = std::string (p);

         entries.push_back (e);

         if (size < e.cmd.size ())
         {
            size = e.cmd.size ();
         }
      });

      delete[] temp;
   });
   /* *INDENT-ON* */

   size++;

   stream << std::endl;

   stream << "================================================" << std::endl;
   stream << "HAN-FUN Example Application : v" << HF_VERSION << std::endl ;
   stream << "================================================" << std::endl << std::endl;

   stream << std::setfill (' ');
   /* *INDENT-OFF* */
   std::for_each (entries.begin (), entries.end (), [&stream, size](entry &e)
   {
      stream << std::left << std::setw (size) << e.cmd << "\t: " << e.help << std::endl;
   });
   /* *INDENT-ON* */

   stream << std::left << std::setw (size) << "h/?" << "\t: " << "this help menu."
          << std::endl << std::endl;
   stream << "Select an Option (Q/q to exit): " << std::endl;

   cache = stream.str();

   _stream << cache;

   return _stream;
}

// =============================================================================
// ICommand::run
// =============================================================================
/*!
 *
 */
// =============================================================================
void ICommand::run (std::string &key, std::vector <std::string> &args)
{
   auto it = registry.find (key);

   if (it == registry.end ())
   {
      LOG (ERROR) << "Command '" << key << "' not found !" << NL;
      ICommand::help (std::cout);
   }
   else
   {
      it->second->run (args);
   }
}

// =============================================================================
// API
// =============================================================================

// =============================================================================
// HF::Application::Handle
// =============================================================================
/*!
 *
 */
// =============================================================================
bool HF::Application::Handle (std::string command)
{
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   if (command.empty () || (command.size () == 1 && command[0] == '\n'))
   {
      ICommand::help (std::cout);
      return false;
   }

   std::istringstream buf (command);
   std::istream_iterator <std::string> beg (buf), end;

   std::vector <std::string> tokens (beg, end);

   std::string cmd = *tokens.begin ();

   std::vector <std::string> args (tokens.begin () + 1, tokens.end ());

   if (cmd == "q" || cmd == "Q")
   {
      return true;
   }
   else if (cmd == "h" || cmd == "?")
   {
      LOG (APP) << "";
      ICommand::help (std::cout);
   }
   else
   {
      ICommand::run (cmd, args);
   }

   LOG (APP) << "> " << std::flush;

   return false;
}

/*! @} */
