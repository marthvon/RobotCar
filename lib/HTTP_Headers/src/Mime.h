#pragma once
#include <Arduino.h>

enum class FILE_TYPE {
    BINARY, MARKUP_HTML, MARKUP_CSS, MARKUP_XML, MARKUP_MARKDOWN, MARKUP_XHTML, MARKUP_XUL,
    TEXT_PLAIN, TEXT_RTF, TEXT_PDF, TEXT_WORD, TEXT_WORD_XML, TEXT_EPUB, TEXT_OPEN_WORD, TEXT_ABIWORD, TEXT_AMAZON_KINDLE, 
    GRAPHICS_JPEG, GRAPHICS_PNG, GRAPHICS_ICON, GRAPHICS_GIF, GRAPHICS_WEBP, GRAPHICS_TIFF, GRAPHICS_SVG, GRAPHICS_BMP, GRAPHICS_AVIF, GRAPHICS_VISIO, GRAPHICS_CALENDAR,
    AUDIO_MP3, AUDIO_WAV, AUDIO_AAC, AUDIO_OGG, AUDIO_OGX, AUDIO_WEBM, AUDIO_MIDI, AUDIO_XMIDI, AUDIO_3GPP, AUDIO_3GPP2, AUDIO_OPUS, AUDIO_CD,
    VIDEO_MP4, VIDEO_MPEG, VIDEO_WEBM, VIDEO_AVI, VIDEO_OGG, VIDEO_TS, VIDEO_3GPP, VIDEO_3GPP2,
    STORAGE_CSV, STORAGE_JSON, STORAGE_JSONLD, STORAGE_EXCEL, STORAGE_EXCEL_XML, STORAGE_OPEN_SPREADSHEET,
    COMPRESSED_FILE_ZIP, COMPRESSED_FILE_RAR, COMPRESSED_FILE_TAR, COMPRESSED_FILE_ARCHIVE, COMPRESSED_FILE_7ZIP, COMPRESSED_FILE_GZIP, COMPRESSED_FILE_BZIP, COMPRESSED_FILE_BZIP2, COMPRESSED_FILE_APPLE_INSTALLER, 
    SCRIPTS_JAVASCRIPT, SCRIPTS_JAVASCRIPT_MODULE, SCRIPTS_PHP, SCRIPTS_JAVA_ARCHIVE, SCRIPTS_BOURNE_SHELL, SCRIPTS_C_SHELL,
    FONTS_TRUETYPE, FONTS_WOFF, FONTS_WOFF2, FONTS_OPENFONT, FONTS_OPENFONT_EMBEDDED,
    MULTIMEDIA_POWERPOINT, MULTIMEDIA_POWERPOINT_XML, MULTIMEDIA_OPEN_PRESENTATION 
};

static const String get_MIME_type(FILE_TYPE ft);

enum CONTENT_ENCODING {
    GZIP,
    COMPRESS,
    DEFLATE,
    B_R
};

/**
 * @brief Content Types
 * Extension	Kind of document	    MIME Type
 * .htm, .html	HTML			        text/html
 * .css		    Cascading Style Sheets 	text/css
 * .md          Markdown                text/markdown
  * .xhtml		XHTML			        application/xhtml+xml
 * .xml		    XML			            application/xml is recommended as of RFC 7303 
 * .xul		    XUL			            application/vnd.mozilla.xul+xml
 * .bin		    Binary Data		        application/octet-stream

 *              ***STORAGE AND DATABASES***
 * .csv		    Comma-separated values 	text/csv
 * .json		JSON format		        application/json
 * .jsonld		JSON-LD format		    application/ld+json
 * .xls		    Microsoft Excel		    application/vnd.ms-excel
 * .xlsx		MS Excel (OpenXML)	    application/vnd.openxmlformats-officedocument.spreadsheetml.sheet 
 * .ods		    OpenDocumentSpreadsheet application/vnd.oasis.opendocument.spreadsheet

 *              ***COMPRESSED FILE DIRECTORIES***
 * .7z		    7-zip archive		    application/x-7z-compressed
 * .zip		    ZIP archive		        application/zip
 * .gz		    GZip Compressed Archive	application/gzip
 * .rar		    RAR archive		        application/vnd.rar
 * .bz		    BZip archive		    application/x-bzip
 * .bz2		    BZip2 archive		    application/x-bzip2
 * .tar		    TAR			            application/x-tar
 * .arc		    Archive document 	    application/x-freearc
 * .mpkg		Apple Installer Package	application/vnd.apple.installer+xml

 *              ***TEXT***
 * .txt		    Text			        text/plain
 * .rtf		    Rich Text Format (RTF)	application/rtf
 * .pdf		    PDF			            application/pdf
 * .doc		    Microsoft Word		    application/msword
 * .docx		MSWord (OpenXML)	    application/vnd.openxmlformats-officedocument.wordprocessingml.document
 * .epub		Electronic publication	application/epub+zip
 * .odt		    OpenDocumentText	    application/vnd.oasis.opendocument.text
 * .abw		    AbiWord document	    application/x-abiword
 * .azw		    Amazon Kindle 		    application/vnd.amazon.ebook

 *              ***GRAPHICS***
 * .jpeg, .jpg	JPEG images		        image/jpeg
 * .png		    PortableNetworkGraphics	image/png
 * .gif		    GIF			            image/gif
 * .ico		    Icon format		        image/vnd.microsoft.icon
 * .avif	    AVIF image		        image/avif
 * .svg		    SVG			            image/svg+xml
 * .bmp		    Bitmap Graphics		    image/bmp
 * .tif, .tiff	TIFF			        image/tiff
 * .webp		WEBP image		        image/webp
 * .vsd		    Microsoft Visio		    application/vnd.visio
 * .ics		    iCalendar format	    text/calendar

 *              ***AUDIO***
 * .mp3		    MP3 audio		        audio/mpeg
 * .mid, .midi	MIDI			        audio/midi, audio/x-midi
 * .wav		    Waveform Audio Format	audio/wav
 * .weba		WEBM audio		        audio/webm
 * .aac		    AAC audio		        audio/aac
 * .oga		    OGG audio		        audio/ogg
 * .cda		    CD audio		        application/x-cdf
 * .opus		Opus audio		        audio/opus
 * .ogx		    OGG			            application/ogg

 *              ***VIDEOS***
 * .mp4		    MP4 video		        video/mp4
 * .mpeg		MPEG Video		        video/mpeg
 * .ts		    MPEG transport stream	video/mp2t
 * .avi		    AVI			            video/x-msvideo
 * .webm		WEBM video		        video/webm
 * .3gp		    3GPP 			        video/3gpp; audio/3gpp if it doesn't contain video
 * .3g2		    3GPP2			        video/3gpp2; audio/3gpp2 if it doesn't contain video
 * .ogv		    OGG video		        video/ogg

 *              ***PROGRAMMABLE***
 * .js		    JavaScript		        text/javascript (Specifications: HTML and RFC 9239)
 * .mjs		    JavaScript module	    text/javascript
 * .php		    Hypertext Preprocessor	application/x-httpd-php
 * .jar		    Java Archive (JAR)	    application/java-archive
 * .sh		    Bourne shell script	    application/x-sh
 * .csh		    C-Shell script		    application/x-csh

 *              ***FONTS***
 * .ttf		    TrueType Font		    font/ttf
 * .woff		WOFF			        font/woff
 * .woff2		WOFF			        font/woff2
 * .otf		    OpenType font		    font/otf
 * .eot		    MSEmbeddedOpenTypeFonts application/vnd.ms-fontobject 

 *              ***MULTIMEDIA*** 
 * .ppt		    Microsoft PowerPoint	application/vnd.ms-powerpoint
 * .pptx	    MS PowerPoint OpenXML	application/vnd.openxmlformats-officedocument.presentationml.presentation
 * .odp		    OpenDocumentPresentatio	application/vnd.oasis.opendocument.presentation
 */