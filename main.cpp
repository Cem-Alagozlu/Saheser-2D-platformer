#include "stdafx.h"
#include "Core.h"
#include <ctime>
#include <locale.h>

void StartHeapControl( );
void DumpMemoryLeaks( );

int main( int argc, char *argv[] )
{
	srand(int(time(nullptr)));
	{ // Make sure stack objects go out of scope before memory leaks are dumped
		StartHeapControl();
		Core core{ Window{ "Saheser - Cem Alagozlu - 1DAE16", 1280, 720 } };
		core.Run();
	}
	// ik heb een paar static (global) variabelen, deze worden na de programma verwijdert
	// dus -> mem leaks terwijl ze wel worden verwijdert
	// DumpMemoryLeaks( );
	// static word delete na de return
	return 0;
}

void StartHeapControl( )
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, 0 );

	// Report detected leaks when the program exits
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 600 );
#endif
}

void DumpMemoryLeaks( )
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks( );
#endif
}

