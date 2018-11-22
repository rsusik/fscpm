import os, sys, random, argparse, gzip, shutil
from urllib.request import urlopen

set_loc = './sets'
pat_loc = './patterns'

parser = argparse.ArgumentParser(description='Generates r patterns of length m for the circular pattern matching problem', 
	epilog="Example:\npython3 generate_patterns.py -c english.10MB -r 100,1000 -m 8,32")
parser.add_argument("-c", "--corpus", dest='c', type=str, default='english.100MB', help="corpus")
parser.add_argument("-m", "--length", dest='m', type=str, default='8,16,32,64', help="pattern length[s] (e.g. 8,16,32)")

args = parser.parse_args()

c_args_list	= args.c.split(',')
m_args_list	= args.m.split(',')

r=100



pizza_corpus = {
	'proteins.50MB': 'http://pizzachili.dcc.uchile.cl/texts/protein/proteins.50MB.gz',
	'proteins.100MB': 'http://pizzachili.dcc.uchile.cl/texts/protein/proteins.100MB.gz',
	'proteins.200MB': 'http://pizzachili.dcc.uchile.cl/texts/protein/proteins.200MB.gz',
	'sources.50MB': 'http://pizzachili.dcc.uchile.cl/texts/code/sources.50MB.gz',
	'sources.100MB': 'http://pizzachili.dcc.uchile.cl/texts/code/sources.100MB.gz',
	'sources.200MB': 'http://pizzachili.dcc.uchile.cl/texts/code/sources.200MB.gz',
	'dna.50MB': 'http://pizzachili.dcc.uchile.cl/texts/dna/dna.50MB.gz',
	'dna.100MB': 'http://pizzachili.dcc.uchile.cl/texts/dna/dna.100MB.gz',
	'dna.200MB': 'http://pizzachili.dcc.uchile.cl/texts/dna/dna.200MB.gz',
	'english.50MB': 'http://pizzachili.dcc.uchile.cl/texts/nlang/english.50MB.gz',
	'english.100MB': 'http://pizzachili.dcc.uchile.cl/texts/nlang/english.100MB.gz',
	'english.200MB': 'http://pizzachili.dcc.uchile.cl/texts/nlang/english.200MB.gz',
	'english.1024MB':'http://pizzachili.dcc.uchile.cl/texts/nlang/english.1024MB.gz',
	'xml.50MB': 'http://pizzachili.dcc.uchile.cl/texts/xml/dblp.xml.50MB.gz',
	'xml.100MB': 'http://pizzachili.dcc.uchile.cl/texts/xml/dblp.xml.100MB.gz',
	'xml.200MB': 'http://pizzachili.dcc.uchile.cl/texts/xml/dblp.xml.200MB.gz',
}

def check_corpus_existance(corpus):
	filename = "{}/{}".format(set_loc, corpus)
	if os.path.isfile(filename):
		return True
	if corpus not in pizza_corpus:
		return False
	print("Warning: Corpus does NOT exists. Trying to download (it may take a while).")
	sys.stdout.flush()
	url = pizza_corpus[c]
	with urlopen(url) as ret:
		if ret.code != 200:
			return False
	gz_filename = "{}.gz".format(filename)
	os.makedirs(os.path.dirname(gz_filename), exist_ok=True)
	with urlopen(url) as response, open(gz_filename, 'wb') as gz_file:
		shutil.copyfileobj(response, gz_file)
	if os.path.isfile(gz_filename):
		with gzip.open(gz_filename, 'rb') as gz_file, open(filename, 'wb') as dest_file:
			dest_file.write(gz_file.read())
		if os.path.isfile(filename):
			os.remove(gz_filename)
			return True
	return False

for c in c_args_list:
	if check_corpus_existance(c) == False:
		print("Error: corpus {} does NOT exists".format(c))
		exit(100)



for c in c_args_list:
	for m_el in m_args_list:
		m = int(m_el)

		corp_filename = "{}/{}".format(set_loc, c)
		if not os.path.isfile(corp_filename):
			print("Error: The set file not found ({})".format(corp_filename))
			exit()

		with open(corp_filename, "rb") as corpus: 
			t = corpus.read()

			output_filename = "{}/patterns.{}.{}.bin".format(pat_loc, c, m)
			os.makedirs(os.path.dirname(output_filename), exist_ok=True)
			with open(output_filename, "wb") as outFile:

				for i in range(int(r / 2)):
					startPos = random.randint(0, len(t) - m)
					rotation = random.randint(0, m - 1)
					patt = t[startPos:startPos + m]
					patt = patt[rotation:] + patt[:rotation]
					outFile.write(patt)
					outFile.write(patt[::-1])
