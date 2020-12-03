#include <winsock2.h>
#include <stdio.h>
#include "server.h"

/*
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers#Response_context
Content-Length   - The size of the resource, in decimal number of bytes.
Content-Type     - Indicates the media type of the resource.
Content-Encoding - Used to specify the compression algorithm.
Content-Language - Describes the human language(s) intended for the audience, so that it allows a user to differentiate according to the users' own preferred language.
Content-Location - Indicates an alternate location for the returned data. 
*/

BOOL FileExists(LPCTSTR szPath) {
	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

char* get_content_type(char *name) {
    char* extension = strchr(name, '.');
    if      (!strcmp(extension, ".html")) { return "text/html";       }
    else if (!strcmp(extension, ".ico"))  { return "image/webp";      }
    else if (!strcmp(extension, ".css"))  { return "text/css";        }
    else if (!strcmp(extension, ".jpg"))  { return "image/jpeg";      }
    else if (!strcmp(extension, ".js"))   { return "text/javascript"; }
    return "*/*";
}

char* get_header(RESPONSE* rs) {
    if (!FileExists(rs->filepath)) {
        fprintf(stderr, " -- 404 Not Found: %s", rs->filename);
        rs->error = 404;
        return "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
    }
	
    char header[1024] = {0};
    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(rs->filename));
    return strdup(header);
}