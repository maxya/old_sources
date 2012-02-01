========================================================================
       STATIC LIBRARY : TheLibrary
========================================================================

������������ ����
� ������ v1.2 � ������:

//////////////////////////////////////////////////////////////////////
[from]	
	int buffsize = m_buff.GetFileSize();
	m_buff.CloseAndDetach(&tempDest);
	. . .
	m_buff.OpenRAM(tempDest, buffsize-4);
[to]
	int buffsize = m_buff.GetFileSize();
	m_buff.ExtractBuffer(&tempDest);
	. . .
	m_buff.SetFileSize (buffsize-4);

�������� ������ ����� � ����� �� �����,
�.�. ���� ��� ���������� ������ �� ����������.
���� ����� �������� ����� � ������ � �����, ���� �����
��������� ���� ������� ��� ToogleDeleteOnClose(FALSE).

//////////////////////////////////////////////////////////////////////

[from]
	File.ToogleCompression (TRUE);
	File.OpenHDD (ffd.cFileName, GENERIC_READ, 0, OPEN_EXISTING);
	.  .  .
	File.Close ();
[to]
	File.ToogleCompression (TRUE);
	File.OpenHDD (ffd.cFileName, GENERIC_READ, 0, OPEN_EXISTING);
	{
		SWFILE fileMirror;
		SWCOMPRESS packer;
		LPVOID pvMem;
		fileMirror.ToogleDeleteOnClose (FALSE);
		fileMirror.OpenRAM ();
		packer.Decode (File, fileMirror);
		File.Close ();
		fileMirror.ExtractBuffer (&pvMem);
		File.OpenRAM (pvMem, fileMirror.GetFileSize ());
		fileMirror.Close ();
	}
	File.Close ();
