#include <stdio.h>
#include <string.h>

#include "unzip.h"

#define dir_delimter '/'
#define MAX_FILENAME 512
#define READ_SIZE 8192

int main( int argc, char **argv )
{
    if ( argc < 2 )
    {
        printf( "usage:\n%s {file to unzip}\n", argv[ 0 ] );
        return -1;
    }

   
    unzFile *zipfile = unzOpen( argv[ 1 ] );
    if ( zipfile == NULL )
    {
        printf( "%s: not found\n" );
        return -1;
    }

    
    unz_global_info global_info;
    if ( unzGetGlobalInfo( zipfile, &global_info ) != UNZ_OK )
    {
        printf( "could not read file global info\n" );
        unzClose( zipfile );
        return -1;
    }

 
    char read_buffer[ READ_SIZE ];

    
    uLong i;
    for ( i = 0; i < global_info.number_entry; ++i )
    {
        
        unz_file_info file_info;
        char filename[ MAX_FILENAME ];
        if ( unzGetCurrentFileInfo(
            zipfile,
            &file_info,
            filename,
            MAX_FILENAME,
            NULL, 0, NULL, 0 ) != UNZ_OK )
        {
            printf( "could not read file info\n" );
            unzClose( zipfile );
            return -1;
        }
        
   

            
            FILE *out = fopen( filename, "wb" );
            if ( out == NULL )
            {
                printf( "could not open destination file\n" );
                unzCloseCurrentFile( zipfile );
                unzClose( zipfile );
                return -1;
            }

            int error = UNZ_OK;
           

            fclose( out );
        }

        unzCloseCurrentFile( zipfile );

        
    }

    unzClose( zipfile );

    return 0;
}
