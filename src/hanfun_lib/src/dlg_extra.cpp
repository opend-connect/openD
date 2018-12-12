#ifdef DLG_HF_NO_ASSERT

#include <iostream>


void _dlg_assert (const char* _err, const char* _file, int _line)
{
	std::cout.clear ();
	std::cout << " !! ASSERT DETECTED: " << _err << " " << _file << " " << _line << " !!" << std::endl;
	std::cout.clear ();
	std::cerr.clear ();
}

#endif
