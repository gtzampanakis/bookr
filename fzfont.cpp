/*
 * Bookr: document reader for the Sony PSP 
 * Copyright (C) 2005 Carlos Carrasco Martinez (carloscm at gmail dot com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef MAC
static void* memalign(int t, int s) {
	return malloc(s);
}
#else
#include <malloc.h>
#endif

#include "fzfont.h"

FZFont::FZFont() : metrics(0) {
}

FZFont::~FZFont() {
	if (metrics)
		free(metrics);
	metrics = 0;
}


int ISO_8859_7_CHARMAP(unsigned char byte) {
	int result = -1;
	switch(byte) {
		case 0x00:	result = 0x0000; break;	//	NULL
		case 0x01:	result = 0x0001; break;	//	START OF HEADING
		case 0x02:	result = 0x0002; break;	//	START OF TEXT
		case 0x03:	result = 0x0003; break;	//	END OF TEXT
		case 0x04:	result = 0x0004; break;	//	END OF TRANSMISSION
		case 0x05:	result = 0x0005; break;	//	ENQUIRY
		case 0x06:	result = 0x0006; break;	//	ACKNOWLEDGE
		case 0x07:	result = 0x0007; break;	//	BELL
		case 0x08:	result = 0x0008; break;	//	BACKSPACE
		case 0x09:	result = 0x0009; break;	//	HORIZONTAL TABULATION
		case 0x0A:	result = 0x000A; break;	//	LINE FEED
		case 0x0B:	result = 0x000B; break;	//	VERTICAL TABULATION
		case 0x0C:	result = 0x000C; break;	//	FORM FEED
		case 0x0D:	result = 0x000D; break;	//	CARRIAGE RETURN
		case 0x0E:	result = 0x000E; break;	//	SHIFT OUT
		case 0x0F:	result = 0x000F; break;	//	SHIFT IN
		case 0x10:	result = 0x0010; break;	//	DATA LINK ESCAPE
		case 0x11:	result = 0x0011; break;	//	DEVICE CONTROL ONE
		case 0x12:	result = 0x0012; break;	//	DEVICE CONTROL TWO
		case 0x13:	result = 0x0013; break;	//	DEVICE CONTROL THREE
		case 0x14:	result = 0x0014; break;	//	DEVICE CONTROL FOUR
		case 0x15:	result = 0x0015; break;	//	NEGATIVE ACKNOWLEDGE
		case 0x16:	result = 0x0016; break;	//	SYNCHRONOUS IDLE
		case 0x17:	result = 0x0017; break;	//	END OF TRANSMISSION BLOCK
		case 0x18:	result = 0x0018; break;	//	CANCEL
		case 0x19:	result = 0x0019; break;	//	END OF MEDIUM
		case 0x1A:	result = 0x001A; break;	//	SUBSTITUTE
		case 0x1B:	result = 0x001B; break;	//	ESCAPE
		case 0x1C:	result = 0x001C; break;	//	FILE SEPARATOR
		case 0x1D:	result = 0x001D; break;	//	GROUP SEPARATOR
		case 0x1E:	result = 0x001E; break;	//	RECORD SEPARATOR
		case 0x1F:	result = 0x001F; break;	//	UNIT SEPARATOR
		case 0x20:	result = 0x0020; break;	//	SPACE
		case 0x21:	result = 0x0021; break;	//	EXCLAMATION MARK
		case 0x22:	result = 0x0022; break;	//	QUOTATION MARK
		case 0x23:	result = 0x0023; break;	//	NUMBER SIGN
		case 0x24:	result = 0x0024; break;	//	DOLLAR SIGN
		case 0x25:	result = 0x0025; break;	//	PERCENT SIGN
		case 0x26:	result = 0x0026; break;	//	AMPERSAND
		case 0x27:	result = 0x0027; break;	//	APOSTROPHE
		case 0x28:	result = 0x0028; break;	//	LEFT PARENTHESIS
		case 0x29:	result = 0x0029; break;	//	RIGHT PARENTHESIS
		case 0x2A:	result = 0x002A; break;	//	ASTERISK
		case 0x2B:	result = 0x002B; break;	//	PLUS SIGN
		case 0x2C:	result = 0x002C; break;	//	COMMA
		case 0x2D:	result = 0x002D; break;	//	HYPHEN-MINUS
		case 0x2E:	result = 0x002E; break;	//	FULL STOP
		case 0x2F:	result = 0x002F; break;	//	SOLIDUS
		case 0x30:	result = 0x0030; break;	//	DIGIT ZERO
		case 0x31:	result = 0x0031; break;	//	DIGIT ONE
		case 0x32:	result = 0x0032; break;	//	DIGIT TWO
		case 0x33:	result = 0x0033; break;	//	DIGIT THREE
		case 0x34:	result = 0x0034; break;	//	DIGIT FOUR
		case 0x35:	result = 0x0035; break;	//	DIGIT FIVE
		case 0x36:	result = 0x0036; break;	//	DIGIT SIX
		case 0x37:	result = 0x0037; break;	//	DIGIT SEVEN
		case 0x38:	result = 0x0038; break;	//	DIGIT EIGHT
		case 0x39:	result = 0x0039; break;	//	DIGIT NINE
		case 0x3A:	result = 0x003A; break;	//	COLON
		case 0x3B:	result = 0x003B; break;	//	SEMICOLON
		case 0x3C:	result = 0x003C; break;	//	LESS-THAN SIGN
		case 0x3D:	result = 0x003D; break;	//	EQUALS SIGN
		case 0x3E:	result = 0x003E; break;	//	GREATER-THAN SIGN
		case 0x3F:	result = 0x003F; break;	//	QUESTION MARK
		case 0x40:	result = 0x0040; break;	//	COMMERCIAL AT
		case 0x41:	result = 0x0041; break;	//	LATIN CAPITAL LETTER A
		case 0x42:	result = 0x0042; break;	//	LATIN CAPITAL LETTER B
		case 0x43:	result = 0x0043; break;	//	LATIN CAPITAL LETTER C
		case 0x44:	result = 0x0044; break;	//	LATIN CAPITAL LETTER D
		case 0x45:	result = 0x0045; break;	//	LATIN CAPITAL LETTER E
		case 0x46:	result = 0x0046; break;	//	LATIN CAPITAL LETTER F
		case 0x47:	result = 0x0047; break;	//	LATIN CAPITAL LETTER G
		case 0x48:	result = 0x0048; break;	//	LATIN CAPITAL LETTER H
		case 0x49:	result = 0x0049; break;	//	LATIN CAPITAL LETTER I
		case 0x4A:	result = 0x004A; break;	//	LATIN CAPITAL LETTER J
		case 0x4B:	result = 0x004B; break;	//	LATIN CAPITAL LETTER K
		case 0x4C:	result = 0x004C; break;	//	LATIN CAPITAL LETTER L
		case 0x4D:	result = 0x004D; break;	//	LATIN CAPITAL LETTER M
		case 0x4E:	result = 0x004E; break;	//	LATIN CAPITAL LETTER N
		case 0x4F:	result = 0x004F; break;	//	LATIN CAPITAL LETTER O
		case 0x50:	result = 0x0050; break;	//	LATIN CAPITAL LETTER P
		case 0x51:	result = 0x0051; break;	//	LATIN CAPITAL LETTER Q
		case 0x52:	result = 0x0052; break;	//	LATIN CAPITAL LETTER R
		case 0x53:	result = 0x0053; break;	//	LATIN CAPITAL LETTER S
		case 0x54:	result = 0x0054; break;	//	LATIN CAPITAL LETTER T
		case 0x55:	result = 0x0055; break;	//	LATIN CAPITAL LETTER U
		case 0x56:	result = 0x0056; break;	//	LATIN CAPITAL LETTER V
		case 0x57:	result = 0x0057; break;	//	LATIN CAPITAL LETTER W
		case 0x58:	result = 0x0058; break;	//	LATIN CAPITAL LETTER X
		case 0x59:	result = 0x0059; break;	//	LATIN CAPITAL LETTER Y
		case 0x5A:	result = 0x005A; break;	//	LATIN CAPITAL LETTER Z
		case 0x5B:	result = 0x005B; break;	//	LEFT SQUARE BRACKET
		case 0x5C:	result = 0x005C; break;	//	REVERSE SOLIDUS
		case 0x5D:	result = 0x005D; break;	//	RIGHT SQUARE BRACKET
		case 0x5E:	result = 0x005E; break;	//	CIRCUMFLEX ACCENT
		case 0x5F:	result = 0x005F; break;	//	LOW LINE
		case 0x60:	result = 0x0060; break;	//	GRAVE ACCENT
		case 0x61:	result = 0x0061; break;	//	LATIN SMALL LETTER A
		case 0x62:	result = 0x0062; break;	//	LATIN SMALL LETTER B
		case 0x63:	result = 0x0063; break;	//	LATIN SMALL LETTER C
		case 0x64:	result = 0x0064; break;	//	LATIN SMALL LETTER D
		case 0x65:	result = 0x0065; break;	//	LATIN SMALL LETTER E
		case 0x66:	result = 0x0066; break;	//	LATIN SMALL LETTER F
		case 0x67:	result = 0x0067; break;	//	LATIN SMALL LETTER G
		case 0x68:	result = 0x0068; break;	//	LATIN SMALL LETTER H
		case 0x69:	result = 0x0069; break;	//	LATIN SMALL LETTER I
		case 0x6A:	result = 0x006A; break;	//	LATIN SMALL LETTER J
		case 0x6B:	result = 0x006B; break;	//	LATIN SMALL LETTER K
		case 0x6C:	result = 0x006C; break;	//	LATIN SMALL LETTER L
		case 0x6D:	result = 0x006D; break;	//	LATIN SMALL LETTER M
		case 0x6E:	result = 0x006E; break;	//	LATIN SMALL LETTER N
		case 0x6F:	result = 0x006F; break;	//	LATIN SMALL LETTER O
		case 0x70:	result = 0x0070; break;	//	LATIN SMALL LETTER P
		case 0x71:	result = 0x0071; break;	//	LATIN SMALL LETTER Q
		case 0x72:	result = 0x0072; break;	//	LATIN SMALL LETTER R
		case 0x73:	result = 0x0073; break;	//	LATIN SMALL LETTER S
		case 0x74:	result = 0x0074; break;	//	LATIN SMALL LETTER T
		case 0x75:	result = 0x0075; break;	//	LATIN SMALL LETTER U
		case 0x76:	result = 0x0076; break;	//	LATIN SMALL LETTER V
		case 0x77:	result = 0x0077; break;	//	LATIN SMALL LETTER W
		case 0x78:	result = 0x0078; break;	//	LATIN SMALL LETTER X
		case 0x79:	result = 0x0079; break;	//	LATIN SMALL LETTER Y
		case 0x7A:	result = 0x007A; break;	//	LATIN SMALL LETTER Z
		case 0x7B:	result = 0x007B; break;	//	LEFT CURLY BRACKET
		case 0x7C:	result = 0x007C; break;	//	VERTICAL LINE
		case 0x7D:	result = 0x007D; break;	//	RIGHT CURLY BRACKET
		case 0x7E:	result = 0x007E; break;	//	TILDE
		case 0x7F:	result = 0x007F; break;	//	DELETE
		case 0x80:	result = 0x0080; break;	//	<control>
		case 0x81:	result = 0x0081; break;	//	<control>
		case 0x82:	result = 0x0082; break;	//	<control>
		case 0x83:	result = 0x0083; break;	//	<control>
		case 0x84:	result = 0x0084; break;	//	<control>
		case 0x85:	result = 0x0085; break;	//	<control>
		case 0x86:	result = 0x0086; break;	//	<control>
		case 0x87:	result = 0x0087; break;	//	<control>
		case 0x88:	result = 0x0088; break;	//	<control>
		case 0x89:	result = 0x0089; break;	//	<control>
		case 0x8A:	result = 0x008A; break;	//	<control>
		case 0x8B:	result = 0x008B; break;	//	<control>
		case 0x8C:	result = 0x008C; break;	//	<control>
		case 0x8D:	result = 0x008D; break;	//	<control>
		case 0x8E:	result = 0x008E; break;	//	<control>
		case 0x8F:	result = 0x008F; break;	//	<control>
		case 0x90:	result = 0x0090; break;	//	<control>
		case 0x91:	result = 0x0091; break;	//	<control>
		case 0x92:	result = 0x0092; break;	//	<control>
		case 0x93:	result = 0x0093; break;	//	<control>
		case 0x94:	result = 0x0094; break;	//	<control>
		case 0x95:	result = 0x0095; break;	//	<control>
		case 0x96:	result = 0x0096; break;	//	<control>
		case 0x97:	result = 0x0097; break;	//	<control>
		case 0x98:	result = 0x0098; break;	//	<control>
		case 0x99:	result = 0x0099; break;	//	<control>
		case 0x9A:	result = 0x009A; break;	//	<control>
		case 0x9B:	result = 0x009B; break;	//	<control>
		case 0x9C:	result = 0x009C; break;	//	<control>
		case 0x9D:	result = 0x009D; break;	//	<control>
		case 0x9E:	result = 0x009E; break;	//	<control>
		case 0x9F:	result = 0x009F; break;	//	<control>
		case 0xA0:	result = 0x00A0; break;	//	NO-BREAK SPACE
		case 0xA1:	result = 0x2018; break;	//	LEFT SINGLE QUOTATION MARK
		case 0xA2:	result = 0x2019; break;	//	RIGHT SINGLE QUOTATION MARK
		case 0xA3:	result = 0x00A3; break;	//	POUND SIGN
		case 0xA4:	result = 0x20AC; break;	//	EURO SIGN
		case 0xA5:	result = 0x20AF; break;	//	DRACHMA SIGN
		case 0xA6:	result = 0x00A6; break;	//	BROKEN BAR
		case 0xA7:	result = 0x00A7; break;	//	SECTION SIGN
		case 0xA8:	result = 0x00A8; break;	//	DIAERESIS
		case 0xA9:	result = 0x00A9; break;	//	COPYRIGHT SIGN
		case 0xAA:	result = 0x037A; break;	//	GREEK YPOGEGRAMMENI
		case 0xAB:	result = 0x00AB; break;	//	LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
		case 0xAC:	result = 0x00AC; break;	//	NOT SIGN
		case 0xAD:	result = 0x00AD; break;	//	SOFT HYPHEN
		case 0xAF:	result = 0x2015; break;	//	HORIZONTAL BAR
		case 0xB0:	result = 0x00B0; break;	//	DEGREE SIGN
		case 0xB1:	result = 0x00B1; break;	//	PLUS-MINUS SIGN
		case 0xB2:	result = 0x00B2; break;	//	SUPERSCRIPT TWO
		case 0xB3:	result = 0x00B3; break;	//	SUPERSCRIPT THREE
		case 0xB4:	result = 0x0384; break;	//	GREEK TONOS
		case 0xB5:	result = 0x0385; break;	//	GREEK DIALYTIKA TONOS
		case 0xB6:	result = 0x0386; break;	//	GREEK CAPITAL LETTER ALPHA WITH TONOS
		case 0xB7:	result = 0x00B7; break;	//	MIDDLE DOT
		case 0xB8:	result = 0x0388; break;	//	GREEK CAPITAL LETTER EPSILON WITH TONOS
		case 0xB9:	result = 0x0389; break;	//	GREEK CAPITAL LETTER ETA WITH TONOS
		case 0xBA:	result = 0x038A; break;	//	GREEK CAPITAL LETTER IOTA WITH TONOS
		case 0xBB:	result = 0x00BB; break;	//	RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
		case 0xBC:	result = 0x038C; break;	//	GREEK CAPITAL LETTER OMICRON WITH TONOS
		case 0xBD:	result = 0x00BD; break;	//	VULGAR FRACTION ONE HALF
		case 0xBE:	result = 0x038E; break;	//	GREEK CAPITAL LETTER UPSILON WITH TONOS
		case 0xBF:	result = 0x038F; break;	//	GREEK CAPITAL LETTER OMEGA WITH TONOS
		case 0xC0:	result = 0x0390; break;	//	GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
		case 0xC1:	result = 0x0391; break;	//	GREEK CAPITAL LETTER ALPHA
		case 0xC2:	result = 0x0392; break;	//	GREEK CAPITAL LETTER BETA
		case 0xC3:	result = 0x0393; break;	//	GREEK CAPITAL LETTER GAMMA
		case 0xC4:	result = 0x0394; break;	//	GREEK CAPITAL LETTER DELTA
		case 0xC5:	result = 0x0395; break;	//	GREEK CAPITAL LETTER EPSILON
		case 0xC6:	result = 0x0396; break;	//	GREEK CAPITAL LETTER ZETA
		case 0xC7:	result = 0x0397; break;	//	GREEK CAPITAL LETTER ETA
		case 0xC8:	result = 0x0398; break;	//	GREEK CAPITAL LETTER THETA
		case 0xC9:	result = 0x0399; break;	//	GREEK CAPITAL LETTER IOTA
		case 0xCA:	result = 0x039A; break;	//	GREEK CAPITAL LETTER KAPPA
		case 0xCB:	result = 0x039B; break;	//	GREEK CAPITAL LETTER LAMDA
		case 0xCC:	result = 0x039C; break;	//	GREEK CAPITAL LETTER MU
		case 0xCD:	result = 0x039D; break;	//	GREEK CAPITAL LETTER NU
		case 0xCE:	result = 0x039E; break;	//	GREEK CAPITAL LETTER XI
		case 0xCF:	result = 0x039F; break;	//	GREEK CAPITAL LETTER OMICRON
		case 0xD0:	result = 0x03A0; break;	//	GREEK CAPITAL LETTER PI
		case 0xD1:	result = 0x03A1; break;	//	GREEK CAPITAL LETTER RHO
		case 0xD3:	result = 0x03A3; break;	//	GREEK CAPITAL LETTER SIGMA
		case 0xD4:	result = 0x03A4; break;	//	GREEK CAPITAL LETTER TAU
		case 0xD5:	result = 0x03A5; break;	//	GREEK CAPITAL LETTER UPSILON
		case 0xD6:	result = 0x03A6; break;	//	GREEK CAPITAL LETTER PHI
		case 0xD7:	result = 0x03A7; break;	//	GREEK CAPITAL LETTER CHI
		case 0xD8:	result = 0x03A8; break;	//	GREEK CAPITAL LETTER PSI
		case 0xD9:	result = 0x03A9; break;	//	GREEK CAPITAL LETTER OMEGA
		case 0xDA:	result = 0x03AA; break;	//	GREEK CAPITAL LETTER IOTA WITH DIALYTIKA
		case 0xDB:	result = 0x03AB; break;	//	GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA
		case 0xDC:	result = 0x03AC; break;	//	GREEK SMALL LETTER ALPHA WITH TONOS
		case 0xDD:	result = 0x03AD; break;	//	GREEK SMALL LETTER EPSILON WITH TONOS
		case 0xDE:	result = 0x03AE; break;	//	GREEK SMALL LETTER ETA WITH TONOS
		case 0xDF:	result = 0x03AF; break;	//	GREEK SMALL LETTER IOTA WITH TONOS
		case 0xE0:	result = 0x03B0; break;	//	GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS
		case 0xE1:	result = 0x03B1; break;	//	GREEK SMALL LETTER ALPHA
		case 0xE2:	result = 0x03B2; break;	//	GREEK SMALL LETTER BETA
		case 0xE3:	result = 0x03B3; break;	//	GREEK SMALL LETTER GAMMA
		case 0xE4:	result = 0x03B4; break;	//	GREEK SMALL LETTER DELTA
		case 0xE5:	result = 0x03B5; break;	//	GREEK SMALL LETTER EPSILON
		case 0xE6:	result = 0x03B6; break;	//	GREEK SMALL LETTER ZETA
		case 0xE7:	result = 0x03B7; break;	//	GREEK SMALL LETTER ETA
		case 0xE8:	result = 0x03B8; break;	//	GREEK SMALL LETTER THETA
		case 0xE9:	result = 0x03B9; break;	//	GREEK SMALL LETTER IOTA
		case 0xEA:	result = 0x03BA; break;	//	GREEK SMALL LETTER KAPPA
		case 0xEB:	result = 0x03BB; break;	//	GREEK SMALL LETTER LAMDA
		case 0xEC:	result = 0x03BC; break;	//	GREEK SMALL LETTER MU
		case 0xED:	result = 0x03BD; break;	//	GREEK SMALL LETTER NU
		case 0xEE:	result = 0x03BE; break;	//	GREEK SMALL LETTER XI
		case 0xEF:	result = 0x03BF; break;	//	GREEK SMALL LETTER OMICRON
		case 0xF0:	result = 0x03C0; break;	//	GREEK SMALL LETTER PI
		case 0xF1:	result = 0x03C1; break;	//	GREEK SMALL LETTER RHO
		case 0xF2:	result = 0x03C2; break;	//	GREEK SMALL LETTER FINAL SIGMA
		case 0xF3:	result = 0x03C3; break;	//	GREEK SMALL LETTER SIGMA
		case 0xF4:	result = 0x03C4; break;	//	GREEK SMALL LETTER TAU
		case 0xF5:	result = 0x03C5; break;	//	GREEK SMALL LETTER UPSILON
		case 0xF6:	result = 0x03C6; break;	//	GREEK SMALL LETTER PHI
		case 0xF7:	result = 0x03C7; break;	//	GREEK SMALL LETTER CHI
		case 0xF8:	result = 0x03C8; break;	//	GREEK SMALL LETTER PSI
		case 0xF9:	result = 0x03C9; break;	//	GREEK SMALL LETTER OMEGA
		case 0xFA:	result = 0x03CA; break;	//	GREEK SMALL LETTER IOTA WITH DIALYTIKA
		case 0xFB:	result = 0x03CB; break;	//	GREEK SMALL LETTER UPSILON WITH DIALYTIKA
		case 0xFC:	result = 0x03CC; break;	//	GREEK SMALL LETTER OMICRON WITH TONOS
		case 0xFD:	result = 0x03CD; break;	//	GREEK SMALL LETTER UPSILON WITH TONOS
		case 0xFE:	result = 0x03CE; break;	//	GREEK SMALL LETTER OMEGA WITH TONOS
	};

	return result;
};

// based on http://gpwiki.org/index.php/OpenGL_Font_System

FZFont* FZFont::createFromFile(char* fileName, int fontSize, bool autohint) {
	// This initializes FreeType
	FT_Library library;
	if (FT_Init_FreeType(&library) != 0) {
		printf("cannot init freetype\n");
		return 0;
	}

	// Load the font
	FT_Face face;
	if (FT_New_Face(library, fileName, 0, &face) != 0) {
		printf("cannot load font\n");
		return 0;
	}

	return createProto(library, face, fontSize, autohint);
}

FZFont* FZFont::createFromMemory(unsigned char* buffer, int bufferSize, int fontSize, bool autohint) {
	// This initializes FreeType
	FT_Library library;
	if (FT_Init_FreeType(&library) != 0) {
		printf("cannot init freetype\n");
		return 0;
	}

	// Load the font
	FT_Face face;
	if (FT_New_Memory_Face(library, buffer, bufferSize, 0, &face) != 0) {
		printf("cannot load font\n");
		return 0;
	}

	return createProto(library, face, fontSize, autohint);
}

FZFont* FZFont::createProto(FT_Library& library, FT_Face& face, int fontSize, bool autohint) {
	// Margins around characters to prevent them from 'bleeding' into
	// each other.
	int margin = 3;
	int image_height = 0, image_width = 256;

	// Abort if this is not a 'true type', scalable font.
	if (!(face->face_flags & FT_FACE_FLAG_SCALABLE) or !(face->face_flags & FT_FACE_FLAG_HORIZONTAL)) {
		printf("lame font\n");
		return 0;
	}

	// Set the font size
	FT_Set_Pixel_Sizes(face, fontSize, 0);

	// First we go over all the characters to find the max descent
	// and ascent (space required above and below the base of a
	// line of text) and needed image size. There are simpler methods
	// to obtain these with FreeType but they are unreliable.
	int max_descent = 0, max_ascent = 0;
	int space_on_line = image_width - margin, lines = 1;

	int loadMode = FT_LOAD_DEFAULT;
	if (autohint)
		loadMode |= FT_LOAD_FORCE_AUTOHINT;
	for (int i = 0; i < 256; ++i) {
		// Look up the character in the font file.
		int char_index = FT_Get_Char_Index(face, i);
		if (i < 32)
			char_index = 0;
	
		// Render the current glyph.
		FT_Load_Glyph(face, char_index, loadMode);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	
		int advance = (face->glyph->metrics.horiAdvance >> 6) + margin;
		if (advance > space_on_line) {
			space_on_line = image_width - margin;
			++lines;
		}
		space_on_line -= advance;

		int t = face->glyph->bitmap_top;
		if (t > max_ascent)
			max_ascent = t;
		t = face->glyph->bitmap.rows - face->glyph->bitmap_top;
		if (t > max_descent)
			max_descent = t;
	}

	// Compute how high the texture has to be.
	int needed_image_height = (max_ascent + max_descent + margin) * lines + margin;
	// Get the first power of two in which it fits.
	image_height = 16;
	while (image_height < needed_image_height)
		image_height *= 2;

	// Allocate memory for the texture
	FZImage* image = FZImage::createEmpty(image_width, image_height, 256, FZImage::mono8);
	unsigned char* fontTexture = (unsigned char*)image->getData();
	// add clut to texture
	unsigned int* clut = image->getCLUT();
	for (int i = 0; i < 256; i++) {
		clut[i] = 0xffffff | (i << 24);
	}
	//for (int i = 0; i < image_height * image_width; ++i)
	//	fontTexture[i] = 0;
	int fontLineHeight = max_ascent + max_descent + margin;

	// Allocate space for the GlyphEntries
	//std::vector<GlyphEntry> entries(chars.size());
	struct FZCharMetrics* fontMetrics = (FZCharMetrics*)memalign(16, 256 * sizeof(FZCharMetrics));
	memset(fontMetrics, 0, 256 * sizeof(FZCharMetrics));

	// These are the position at which to draw the next glyph
	int x = margin, y = margin + max_ascent;

	// Drawing loop
	for (int i = 0; i < 256; ++i) {

		int char_index = FT_Get_Char_Index(face, ISO_8859_7_CHARMAP(i));

		if (i < 32)
			char_index = 0;
		
		// Render the glyph
		FT_Load_Glyph(face, char_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		
		// See whether the character fits on the current line
		int advance = (face->glyph->metrics.horiAdvance >> 6) + margin;
		if (advance > image_width - x){
			x = margin;
			y += (max_ascent + max_descent + margin);
		}
		
		// Fill in the GlyphEntry
		fontMetrics[i].width = advance - 3;
		fontMetrics[i].xadvance = advance - 3;
		fontMetrics[i].xoffset = 0;
		fontMetrics[i].yoffset = 0;
		fontMetrics[i].height = max_ascent + max_descent;
		fontMetrics[i].x = x;
		fontMetrics[i].y = y - max_ascent;
		
		// Copy the image gotten from FreeType onto the texture
		// at the correct position
		for (int row = 0; row < face->glyph->bitmap.rows; ++row){
			for (int pixel = 0; pixel < face->glyph->bitmap.width; ++pixel){
				fontTexture[(x + face->glyph->bitmap_left + pixel) +
					(y - face->glyph->bitmap_top + row) * image_width] =
					face->glyph->bitmap.buffer[pixel + row * face->glyph->bitmap.pitch];
			}
		}
		x += advance;    
	}

	FT_Done_FreeType(library);

	FZFont* font = new FZFont();
	if (!initFromImage(font, image, false)) {
		font->release();
		font = 0;
	}
	image->release();
	font->metrics = fontMetrics;
	font->lineHeight = fontLineHeight;

	return font;
}

int FZFont::getLineHeight() {
	return lineHeight;
}

FZCharMetrics* FZFont::getMetrics() {
	return metrics;
}

