// =============================================================================
/*!
 * @file       apps/common.h
 *
 * This file contains the definitions for the common functionality in the HAN-FUN
 * example applications.
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

#ifndef HF_APP_COMMON_H
#define HF_APP_COMMON_H

#include <map>

#include "hanfun.h"

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// Command API
// =============================================================================

/*!
 * Example application menu entry API.
 */
struct ICommand
{
   protected:

   //! Command registry.
   static std::map <std::string, ICommand *> registry;

   public:

   /*!
    * Get the command key.
    *
    * @return  the string that represents the command key.
    */
   virtual const std::string &key () const = 0;

   /*!
    * Get the command help documentation.
    *
    * @param [in] format   if \c true the usage string SHOULD be formatted to be displayed
    *                      to the user.
    *
    * @return  command help documentation.
    */
   virtual const std::string usage (bool format = false) const = 0;

   /*!
    * Execute the command code.
    *
    * @param [in] args  the arguments passed to the code.
    */
   virtual void run (std::vector <std::string> &args) = 0;

   /*!
    * Add a command to the registry.
    *
    * @param [in] command  command to be added to the registry.
    */
   static void add (ICommand *command);

   /*!
    * Remove a command to the registry.
    *
    * @param [in] command  command to be removed from the registry.
    */
   static void remove (ICommand *command);

   /*!
    * Find and run the command with the given @c key, using the arguments in @c args.
    *
    * @param [in] cmd   the key for the command to be run.
    * @param [in] args  vector containing the arguments to call the command with.
    */
   static void run (std::string &cmd, std::vector <std::string> &args);

   /*!
    * Generate the help screen, based on the commands in the registry.
    *
    * @param [in] stream   reference to the stream to print the help screen.
    *
    * @return  reference to the stream.
    */
   static std::ostream &help (std::ostream &stream);
};

/*!
 * Parent class for the commands API implementations.
 */
class Command:public ICommand
{
   protected:

   const std::string _key;    //!< Command key.
   const std::string _usage;  //!< Command help string.

   public:

   /*!
    * Constructor.
    *
    * @param __key   command key.
    * @param __usage command help string.
    */
   Command(const char *__key, const char *__usage):
      _key (__key), _usage (__usage)
   {}

   const std::string &key () const
   {
      return _key;
   }

   const std::string usage (bool format = false) const
   {
      if (format)
      {
         std::string result = _usage;
         for(std::string::size_type pos = 0; (pos = result.find(":", pos)) != std::string::npos;
             pos += 3 - 1)
         {
            result.replace(pos, 1, " : ");
         }

         return result;
      }
      else
      {
         return _usage;
      }
   }
};

/*!
 * Helper macro to define new commands.
 */
#define COMMAND(_name, _key, _help)               \
   struct Command_## _name:public Command         \
   {                                              \
      Command_##_name ():Command (_key, _help) {} \
                                                  \
      void run (std::vector <std::string> &args); \
   };                                             \
   Command_##_name command##_name;                \
   void Command_##_name::run (std::vector <std::string> &args)

/*!
 * Helper macro to add a new command to the registry.
 */
#define COMMAND_ADD(_name)             \
   {                                   \
      ICommand::add (&command##_name); \
   }

// =============================================================================
// Parser helpers
// =============================================================================

//! Helper macro to convert a std::string into a number (base 10).
#define STRTOL(X)       strtol (X.c_str (), NULL, 10);

//! Helper macro to convert a std::string into a number (base 16).
#define STRTOL_HEX(X)   strtol (X.c_str (), NULL, 16);

/*! @} */

#endif /* HF_APP_COMMON_H */
