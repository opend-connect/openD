// =============================================================================
/*!
 * @file       apps/main.cpp
 *
 * This file contains the implementation of the main entry point for the
 * HAN-FUN example applications.
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
#include <sstream>

#include "uv.h"

#include "common.h"

#include "application.h"
#include "transport.h"

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// Global Variables.
// =============================================================================

static HF::Application::Transport transport;
static uv_pipe_t stdin_pipe;

// =============================================================================
// Libuv Helpers
// =============================================================================

uv_buf_t alloc_buffer (uv_handle_t *handle, size_t suggested_size);

// =============================================================================
// read_stdin
// =============================================================================
/*!
 * Callback used to receive data from the command line.
 *
 * @param [in] stream   the stream handle the data is coming from.
 * @param [in] nread    number of bytes read.
 * @param [in] buf      buffer containing the data read.
 */
// =============================================================================
static void read_stdin (uv_stream_t *stream, ssize_t nread, uv_buf_t buf)
{
   UNUSED (stream);

   if (nread == -1)
   {
      if (uv_last_error (uv_default_loop ()).code == UV_EOF)
      {
         uv_close ((uv_handle_t *) &stdin_pipe, NULL);
      }
   }
   else if (nread > 0)
   {
      std::string cmd (buf.base, nread);

      if (HF::Application::Handle (cmd))
      {
         transport.destroy ();
         uv_stop (uv_default_loop ());
      }
   }

   if (buf.base)
   {
      free (buf.base);
   }
}

// =============================================================================
// Application Callbacks
// =============================================================================

// =============================================================================
// HF::Application::Saved
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::Application::Saved ()
{
   LOG (INFO) << "Application configuration saved !" << NL;
}

// =============================================================================
// HF::Application::Restored
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::Application::Restored ()
{
   LOG (INFO) << "Application configuration restored !" << NL;
}

/*! @} */

// =============================================================================
// Main
// =============================================================================

int main (int argc, char *argv[])
{
   UNUSED (argc);
   UNUSED (argv);

   uv_loop_t *loop = uv_default_loop ();

#ifdef HF_BASE_APP
   HF::UID::URI *uid = new HF::UID::URI ("hf://base.example.com");
#endif

#ifdef HF_NODE_APP

   if (argc < 2)
   {
      std::cout << "usage : " << argv[0] << " [number]" << std::endl;
      exit (-1);
   }

   std::stringstream ss;
   ss << "hf://node.example.com/" << argv[1];

   HF::UID::URI *uid = new HF::UID::URI (ss.str ());
#endif

   HF::Application::Initialize (transport);
   transport.uid (uid);

   HF::Application::Handle ("?");

   uv_pipe_init (loop, &stdin_pipe, 0);
   uv_pipe_open (&stdin_pipe, 0);

   uv_read_start ((uv_stream_t *) &stdin_pipe, alloc_buffer, read_stdin);

   uv_run (loop, UV_RUN_DEFAULT);

   HF::Application::Save ();

   return 0;
}
