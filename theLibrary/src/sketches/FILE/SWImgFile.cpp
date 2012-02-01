// SWImgFile.cpp: implementation of the CSWImgFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SWImgFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
CSWImgFile::CSWImgFile(long type)
{
	m_stream=NULL;
	m_StorageType = type; //0=file, 1=memory
	m_Position = m_Size = m_Edge = m_DontCloseOnExit = 0;
}
//////////////////////////////////////////////////////////
CSWImgFile::CSWImgFile(FILE* pFile)
{
	m_stream=pFile;
	m_StorageType = 0;
	m_Position = m_Size = m_Edge = 0;
	m_DontCloseOnExit = 1;
}
//////////////////////////////////////////////////////////
CSWImgFile::CSWImgFile(BYTE* pBuffer, DWORD size)
{
	m_stream=pBuffer;
	m_StorageType = 1;
	m_Position = 0;
	m_Size = m_Edge = size;
	m_DontCloseOnExit = 1;
}
void CSWImgFile::Transfer(CSWImgFile &from)
{
	m_stream = from.m_stream;
	m_StorageType = from.m_StorageType;
	m_Position = from.m_Position;
	m_Size = from.m_Size;
	m_Edge = from.m_Edge;
	m_DontCloseOnExit = from.m_DontCloseOnExit;

	from.m_stream = NULL;
}
//////////////////////////////////////////////////////////
CSWImgFile::~CSWImgFile()
{
	Close();
}
//////////////////////////////////////////////////////////
void* CSWImgFile::Open(const char *filename, const char *mode)
{
	if (m_stream) return m_stream;
	switch(m_StorageType){
	case 0:
		return m_stream=fopen(filename, mode);
	case 1:
		{
			m_Position = m_Size = m_Edge = 0;
			return m_stream=malloc(0);
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Close()
{
	if (m_DontCloseOnExit) return -1;
	if (m_stream==0) return false;
	switch(m_StorageType){
	case 0:
		{
			long m_err = fclose((FILE*)m_stream);
			m_stream=NULL;
			return m_err;
		}
	case 1:
		free(m_stream);
		m_stream=NULL;
		return 0;
	}
	return -1;
}
//////////////////////////////////////////////////////////
size_t CSWImgFile::Read(void *buffer, size_t size, size_t count)
{
	if (m_stream==NULL) return 0;
	switch(m_StorageType){
	case 0:
		return fread(buffer, size, count, (FILE*)m_stream );
	case 1:
		{
			if (buffer==NULL) return 0;
			if (m_Position > m_Size) return 0;

			long nCount = count*size;
			if (nCount == 0) return 0;
			
			UINT nRead;
			if (m_Position + nCount > m_Size)
				nRead = (UINT)(m_Size - m_Position);
			else
				nRead = nCount;

			memcpy(buffer, (BYTE*)m_stream + m_Position, nRead);
			m_Position += nRead;

			return (size_t)(nRead/size);
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////
size_t CSWImgFile::Write(const void *buffer, size_t size, size_t count)
{
	if (m_stream==NULL) return 0;
	switch(m_StorageType){
	case 0:
		return fwrite(buffer, size, count, (FILE*)m_stream );
	case 1:
		{
			if (buffer==NULL) return 0;

			long nCount = count*size;
			if (nCount == 0) return 0;

			if (m_Position + nCount > m_Edge) Alloc(m_Position + nCount);

			memcpy((BYTE*)m_stream + m_Position, buffer, nCount);

			m_Position += nCount;

			if (m_Position > m_Size) m_Size = m_Position;
			
			return count;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Seek(long offset, int origin)
{
	if (m_stream==NULL) return 0;
	switch(m_StorageType){
	case 0:
		return fseek((FILE*)m_stream, offset, origin);
	case 1:
		{
			long lNewPos = m_Position;

			if (origin == SEEK_SET)		 lNewPos = offset;
			else if (origin == SEEK_CUR) lNewPos += offset;
			else if (origin == SEEK_END) lNewPos = m_Size + offset;
			else return -1;

			if (lNewPos < 0) return -1;

			m_Position = lNewPos;
			return 0;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Tell()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		return ftell((FILE*)m_stream);
	case 1:
		return m_Position;
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::GetPos(fpos_t *pos)
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		fgetpos((FILE*)m_stream,pos);
		return 0;
	case 1:
		*pos = (fpos_t) m_Position;
		return 0;
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Size()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		{
			long pos,size;
			pos = ftell((FILE*)m_stream);
			fseek((FILE*)m_stream,0,SEEK_END);
			size = ftell((FILE*)m_stream);
			fseek((FILE*)m_stream,pos,SEEK_SET);
			return size;
		}
	case 1:
		return m_Size;
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Flush()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		return fflush((FILE*)m_stream);
		break;
	case 1:
		return 0;
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Eof()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		return feof((FILE*)m_stream);
	case 1:
		return m_Position>=m_Size;
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::Error()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		return ferror((FILE*)m_stream);
	case 1:
		return m_Position>=m_Size;
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::PutC(unsigned char c)
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		return fputc(c, (FILE*)m_stream);
	case 1:
		{
			if (m_Position + 1 > m_Edge) Alloc(m_Position + 1);

			memcpy((BYTE*)m_stream + m_Position, &c, 1);

			m_Position += 1;

			if (m_Position > m_Size) m_Size = m_Position;
			
			return c;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////
long CSWImgFile::GetC()
{
	if (m_stream==NULL) return -1;
	switch(m_StorageType){
	case 0:
		return getc((FILE*)m_stream);
	case 1:
		return *(BYTE*)((BYTE*)m_stream + m_Position);
	}
	return -1;
}
//////////////////////////////////////////////////////////
void* CSWImgFile::Alloc(DWORD dwNewLen)
{
	switch(m_StorageType){
	case 0:
		return m_stream;
	case 1:
		if (dwNewLen > (DWORD)m_Edge)
		{
			// determine new buffer size
			DWORD dwNewBufferSize = (DWORD)m_Edge;
			while (dwNewBufferSize < dwNewLen) dwNewBufferSize += 4096;

			// allocate new buffer
			if (m_stream == NULL) m_stream = malloc(dwNewBufferSize);
			else	m_stream = realloc(m_stream, dwNewBufferSize);

			m_Edge = dwNewBufferSize;
		}
		return m_stream;
	}
	return m_stream;
}
//////////////////////////////////////////////////////////
void CSWImgFile::Free()
{
	Close();
}
//////////////////////////////////////////////////////////
