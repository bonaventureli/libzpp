/* 
 * File:   main.cpp
 * Author: jasonlefley
 *
 * Created on June 17, 2015, 1:20 PM
 */

#include <cstdlib>

#include "Zpp.h"

int main(int argc, char** argv)
{
    int i;
#ifdef ZPP_INCLUDE_OPENALL
    zppZipArchive::openAll("*.zip");
    zppZipArchive::dumpGlobalMap();
#endif /* ZPP_INCLUDE_OPENALL */
    try
    {
#ifndef ZPP_INCLUDE_OPENALL
        zppZipArchive zf1(std::string("zpp.zip"));
#endif /* ZPP_INCLUDE_OPENALL */

        izppstream fp;

        fp.open("readme.htm");
        if (fp.fail())
        {
            std::cerr << "can't open readme.htm" << std::endl;
        }

        std::cout << "<<contents of readme.htm>>" << std::endl;

        while (!fp.eof() && !fp.fail())
        {
            char c;
            // do raw read of file so that newlines get read.
            // alternately, we could do fp->rdbuf() and use the
            // zppstreambuf object instead.
            fp.read(&c, 1);
            std::cout << c;
        }
        std::cout << "<<end of readme.htm>>" << std::endl;

        // EOF will be set here, so we need to clear it.
        fp.clear(std::ios::goodbit);

        // we can seek to the BEGINNING of a file, but nowhere
        // else, currently.
        fp.seekg(0, std::ios::beg);

        i = 0;
        while (i++ < 1000 && !fp.eof() && !fp.fail())
        {
            char c;
            fp.read(&c, 1);
            std::cout << c;
        }
        std::cout << "<<end of dump of first 1000 bytes of readme.htm>>" << std::endl;

        fp.close();

        fp.open("notinzip.txt");
        if (fp.fail())
        {
            std::cerr << "can't open notinzip.txt" << std::endl;
            std::exit(1);
        }

        std::cout << "<<contents of notinzip.txt>>" << std::endl;

        while (!fp.fail() && !fp.eof())
        {
            char c;
            // do raw read of file so that newlines get read.
            // alternately, we could do fp->rdbuf() and use the
            // zppstreambuf object instead.
            fp.read(&c, 1);
            std::cout << c;
        }
        std::cout << "<<end of notinzip.txt>>" << std::endl;

        // EOF will be set here, so we need to clear it.
        fp.clear(std::ios::goodbit);

        // we can seek to the BEGINNING of a file, but nowhere
        // else, currently.
        fp.seekg(0, std::ios::beg);

        i = 0;
        while (i++ < 1000 && !fp.eof() && !fp.fail())
        {
            char c;
            fp.read(&c, 1);
            std::cout << c;
        }
        std::cout << "<<end of dump of first 1000 bytes of notinzip.txt>>" << std::endl;

    }
    catch (zppError e)
    {
        std::cerr << "zppError: " << e.str << std::endl;
    }

    return 0;
}

