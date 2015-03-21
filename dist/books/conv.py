import sys, codecs

path_in = sys.argv[1]
path_out = path_in + '.iso-8859-7.txt'

fin = open(path_in, 'rb')
fout = open(path_out, 'wb')

utf8_data = fin.read()

unicode_data = codecs.decode(utf8_data, 'utf-8')
iso_data = codecs.encode(unicode_data, 'iso-8859-7', 'ignore')

fout.write(iso_data)

fin.close()
fout.close()

