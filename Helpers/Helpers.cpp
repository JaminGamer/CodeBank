#include "pch.h"

char* DeepCopyString(const char* original)
{
	return _strdup(original);
	//char* copy = new char[strlen(original) + 1]; // memory allocation
	//memcpy(copy, original, strlen(original) + 1);

	//return copy;
}

char* LoadFile(const char* filename)
{
	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, filename, "rb");
	if (filehandle)
	{
		// find the length of the file
		fseek(filehandle, 0, SEEK_END); // go to the end
		long size = ftell(filehandle); // read the position in bytes
		rewind(filehandle); // go back to the beginning
							// before we can read, we need to allocate a buffer of the right size
		char* buffer = new char[size];
		fread(buffer, size, 1, filehandle);
		fclose(filehandle);

		return buffer;
	}
	else
	{
		return NULL;
	}
}

void CheckForGLErrors()
{
	GLenum error = glGetError();

	if (error != 0)
	{
		OutputMessage("glGetError: %i\n", error);
#if _WINDOWS
		assert(false);
#endif
	}
}

void WriteStringToFile(char* filename, char* string)
{
	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, filename, "w+");
	if (filehandle)
	{
		fwrite(string, 1, strlen(string), filehandle); // write to file
		fclose(filehandle); // close file stream
	}
	/*
	fopen_S(&filehandle, "filename", "mode")
	FILE* filehandle;
	char* filename;

	Modes:
	"r"
	Opens for reading. If the file does not exist or cannot be found, the fopen_s call fails.
	"r+" = Opens for both reading and writing. (The file must exist.)

	"w"
	Opens an empty file for writing. If the file exists, its contents are destroyed.
	"w+" = Opens an empty file for both reading and writing. If the file exists, its contents are destroyed.

	"a" = Opens for writing at the end of the file (appending) without removing the EOF marker before writing new data to the file. Creates the file if it doesn't exist.
	"a+" = Opens for reading and appending. The appending operation includes the removal of the EOF marker before
	new data is written to the file and the EOF marker is restored after writing is complete.
	Creates the file if it doesn't exist.

	"T" = Specifies a file as temporary. If possible, it is not flushed to disk.

	"D" = Specifies a file as temporary. It is deleted when the last file pointer is closed.
	*/
}
