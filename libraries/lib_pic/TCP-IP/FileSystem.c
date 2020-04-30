/*********************************************************************
 *
 *     File system access interface layer Source File
 *
 *********************************************************************
 * FileName:        FileSystem.c
 * Description:     File system access interface layer
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/
#include "TCPIP.h"

#if defined(STACK_USE_MDD)

int FileSystemInit(void)
{
    #if defined STACK_USE_MPFS2
        MPFSInit();
    #elif defined STACK_USE_MDD 
        return FSInit();
    #endif
    
    return TRUE;
}


FILE_HANDLE FileOpen(const char * fileName, const char *mode)
{
    #if defined STACK_USE_MPFS2
        return MPFSOpen((u8*)fileName);
    #elif defined STACK_USE_MDD 
        return FSfopen(fileName, mode);
    #endif
}

FILE_HANDLE FileOpenROM(const char * fileName, const char *mode)
{
    #if defined STACK_USE_MPFS2
        return MPFSOpenROM((u8*)fileName);
    #elif defined STACK_USE_MDD 
        return FSfopen(fileName, mode);
    #endif
}

int FileClose(FILE_HANDLE fh)
{
    #if defined STACK_USE_MPFS2
        MPFSClose(fh);
    #elif defined STACK_USE_MDD 
        return FSfclose(fh);
    #endif

    return 0;
}

size_t FileRead(void *ptr, size_t size, size_t n, FILE_HANDLE stream)
{
    #if defined STACK_USE_MPFS2
        u16 length;
        length = size * n;
        return MPFSGetArray(stream, (u8*)ptr, length);
    #elif defined STACK_USE_MDD 
        if(ptr == NULL)
        {
            return 0;
        }
        else
        {
            return FSfread(ptr, size, n, stream);
        }
    #endif
}

int FileSeek(FILE_HANDLE stream, long offset, int whence)
{
    #if defined STACK_USE_MPFS2
        BOOL status;
        status = MPFSSeek(stream, offset, whence);
        if(status == TRUE)
            return 0;
        else
            return -1;
        
    #elif defined STACK_USE_MDD 
        return FSfseek(stream, offset, whence);
    #endif
}

long FileTell(FILE_HANDLE fh)
{
    #if defined STACK_USE_MPFS2
        return MPFSGetPosition(fh);
    #elif defined STACK_USE_MDD 
        return FSftell(fh);
    #endif
}

int FileEOF(FILE_HANDLE stream)
{
    #if defined STACK_USE_MPFS2
        return MPFSGetBytesRem(stream);
    #elif defined STACK_USE_MDD 
        return FSfeof(stream);
    #endif
}

int FileFormat(char mode, long int serialNumber, char *volumeID)
{
    #if defined STACK_USE_MPFS2
        int status;
        status = MPFSFormat();
        if(status == MPFS_INVALID_HANDLE)
            return -1;
        else
            return 0;
    #elif defined STACK_USE_MDD 
        return FSformat(mode, serialNumber, volumeID);
    #endif
}

size_t FileWrite(const void *ptr, size_t size, size_t n, FILE_HANDLE stream)
{
    #if defined STACK_USE_MPFS2
        u16 length;
        length = size * n;
        return MPFSPutArray(stream, (u8*)ptr, length);
    #elif defined STACK_USE_MDD 
        return FSfwrite(ptr, size, n, stream);
    #endif
}


size_t FileReadUInt32(u32 *ptr, FILE_HANDLE stream)
{
	u8 databuff[4];
	*ptr=0x00000000;

	#if defined STACK_USE_MPFS2
        u16 retVal;

		retVal=MPFSGetArray(stream, (u8*)ptr, 4);
	
		if(retVal == 4)//Number of Uints of 4 bytes each Read
		{
	
			((u8*)ptr)[3] = databuff[3];
			((u8*)ptr)[2] = databuff[2];
			((u8*)ptr)[1] = databuff[1];
			((u8*)ptr)[0] = databuff[0];

			return 4;//Number of bytes read
		}
		else
			return 0;
		
    #elif defined STACK_USE_MDD 
		size_t retVal; 
       
		retVal= FSfread(databuff, 4, 1, stream);

		if(retVal == 1)//Number of Uints of 4 bytes each Read
		{
	
			((u8*)ptr)[3] = databuff[3];
			((u8*)ptr)[2] = databuff[2];
			((u8*)ptr)[1] = databuff[1];
			((u8*)ptr)[0] = databuff[0];

			return 4;//Number of bytes read
		}
		else
			return 0;
        
    #endif
}

size_t FileReadUInt16(u16 *ptr, FILE_HANDLE stream)
{
	u8 databuff[2];
	*ptr=0x0000;

	#if defined STACK_USE_MPFS2
        u16 retVal;

		retVal=MPFSGetArray(stream, (u8*)ptr, 2);

		if(retVal == 2)//Number of bytes read
		{
			((u8*)ptr)[1]= databuff[1];
			((u8*)ptr)[0]= databuff[0];
			return 2;//Number of bytes read
		}
		else
			return 0;
		
    #elif defined STACK_USE_MDD 
		size_t retVal; 
      
		retVal= FSfread(databuff, 2, 1, stream);

		if(retVal == 1)//Number of Uints of 4 bytes each Read
		{
			((u8*)ptr)[1]= databuff[1];
			((u8*)ptr)[0]= databuff[0];
			return 2;//Number of bytes read
		}
		else
			return 0;
        
    #endif
}


#endif //#if defined(STACK_USE_MDD)
