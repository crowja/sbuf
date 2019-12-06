# Dev notes for sbuf

Maintain a character array of variable size that also has a list of 
character pointers to the strings embedded in it. Support only putc()
for characters and return the list of pointers.

I think this will reduce mallocs if we were to do something different,
but we'll see.

Mainly need a gets() iterator.
