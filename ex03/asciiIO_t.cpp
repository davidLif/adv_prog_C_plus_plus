#include "asciiIO_t.h"

// initializes an empty ascii stream without opening a file
asciiIO_t::asciiIO_t(){
	// let the base class do all the work
}

// intialize a stream and open a file in ascii (text) mode
// again, let the base class do all the work (base class opens the file in text mode by default)
asciiIO_t::asciiIO_t(const string& path, const virtIO_t::access_mode& accessMode) : virtIO_t(path, accessMode)
{}


asciiIO_t::~asciiIO_t(){
	// base implmentation suffices
	// closes the file if open
}

void asciiIO_t::readByParseString(void* container, const string& parse_string)
{

	this->checkStreamValidity();

	// get current position
	long currentPos = this->findCurrentPosition();
	if (currentPos == -1L)
	{
		this->set_io_status(virtIO_t::readErr_e);
		throw runtime_error("Read error(seek)");
	}

	// read one object from the file and store in the container
	if (fscanf(this->getFilePtr(), parse_string.c_str(), container) < 1)
	{
		// restore the position
		this->setFilePosition(currentPos);
		this->set_io_status(virtIO_t::readErr_e);

		throw runtime_error("Read error");
	}

}


void asciiIO_t::writeByParseString(void* container, const string& parse_string)
{

	this->checkStreamValidity();

	// get current position
	long currentPos = this->findCurrentPosition();
	if (currentPos == -1L)
	{
		this->set_io_status(virtIO_t::readErr_e);
		throw runtime_error("Write error(seek)");
	}

	// write one object from from the container into the file
	if (fprintf(this->getFilePtr(), parse_string.c_str(), container) < 1)
	{
		// restore the position
		this->setFilePosition(currentPos);
		this->set_io_status(virtIO_t::writeErr_e);

		throw runtime_error("Write error");
	}
}
