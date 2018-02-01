# CLGR V3.0

dochen, 2018/1/31

I refatoried the SW archtecture, so in this version CLGR code is much easier to read and understand.

In this version, we use below commands to search:

'''
    CLGR -t=text -f=file [-f=file1 -f=file2 ...] -d=directory
'''
-t to specify the text to search, -f to specify in which file(s), -d to specify the search directory. And above file not need to be the complete file name, part also ok. But the directory needs to be complete directory, it's default value is current path.

And if command without -t=text, it means to match files. CLGR will give out files with name contains file1, file2 ... in specify directory.

For more help, run
'''
    CLGR --help
'''

V3.0 is going to work on both linux and windows, but currently it can only works on windows. In V3.1 I will finish linux part(Almost is finished in V3.0). And in later V3.1, I will intruduce a macro __DEBUG__, to help test.

And V3.0 use flexible threads, how many threads will be used totally depends on your machine and the matched files. For example, we have N cores in PC, and we have M files to read, that the thread number is min(N, M)

V3.0 also filter some kinds of files while searching text. for example, we want to seach a text, it will never appear in a mp4 file, or a dll file, so we don't need to read such files.

Also, V3.0 introduced a submodule, which is mingw-std-threads
