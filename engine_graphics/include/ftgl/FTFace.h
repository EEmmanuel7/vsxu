/**
* Project: VSXu: Realtime visual programming language, music/audio visualizer, animation tool and much much more.
*
* @see The Lesser GNU Public License (GPL)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the Lesser GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the Lesser GNU General Public License
* for more details.
*
* You should have received a copy of the Lesser GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef     __FTFace__
#define     __FTFace__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"
#include "FTPoint.h"
#include "FTSize.h"

/**
 * FTFace class provides an abstraction layer for the Freetype Face.
 *
 * @see "Freetype 2 Documentation"
 *
 */
class FTGL_EXPORT FTFace
{
    public:
        /**
         * Opens and reads a face file. Error is set.
         *
         * @param filename  font file name.
         */
        FTFace( const char* filename);

        /**
         * Read face data from an in-memory buffer. Error is set.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTFace( const unsigned char *pBufferBytes, size_t bufferSizeInBytes );

        /**
         * Destructor
         *
         * Disposes of the current Freetype Face.
         */
        virtual ~FTFace();

        /**
         * Attach auxilliary file to font (e.g., font metrics).
         *
         * @param filename  auxilliary font file name.
         * @return          <code>true</code> if file has opened
         *                  successfully.
         */
        bool Attach( const char* filename);

        /**
         * Attach auxilliary data to font (e.g., font metrics) from memory
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         * @return          <code>true</code> if file has opened
         *                  successfully.
         */
        bool Attach( const unsigned char *pBufferBytes, size_t bufferSizeInBytes);

        /**
         * Disposes of the face
         */
        void Close();

        /**
         * Get the freetype face object..
         *
         * @return pointer to an FT_Face.
         */
        FT_Face* Face() const { return ftFace;}
        
        /**
         * Sets the char size for the current face.
         *
         * This doesn't guarantee that the size was set correctly. Clients
         * should check errors.
         *
         * @param size      the face size in points (1/72 inch)
         * @param res       the resolution of the target device.
         * @return          <code>FTSize</code> object
         */
        const FTSize& Size( const unsigned int size, const unsigned int res);

        unsigned int UnitsPerEM() const;

        /**
         * Get the number of character maps in this face.
         *
         * @return character map count.
         */
        unsigned int CharMapCount();

        /**
         * Get a list of character maps in this face.
         *
         * @return pointer to the first encoding.
         */
        FT_Encoding* CharMapList();
        
        /**
         * Gets the kerning vector between two glyphs
         */
        FTPoint KernAdvance( unsigned int index1, unsigned int index2);

        /**
         * Loads and creates a Freetype glyph.
         */
        FT_GlyphSlot Glyph( unsigned int index, FT_Int load_flags);

        /**
         * Gets the number of glyphs in the current face.
         */
        unsigned int GlyphCount() const { return numGlyphs;}

        /**
         * Queries for errors.
         *
         * @return  The current error code.
         */
        FT_Error Error() const { return err; }
        
    private:
        /**
         * The Freetype face
         */
        FT_Face* ftFace;

        /**
         * The size object associated with this face
         */
        FTSize  charSize;
        
        /**
         * The number of glyphs in this face
         */
        int numGlyphs;
        
        FT_Encoding* fontEncodingList;

        /**
         * Current error code. Zero means no error.
         */
        FT_Error err;
};


#endif  //  __FTFace__
