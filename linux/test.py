import subprocess, sys, os, platform, argparse, gzip, shutil
from urllib.request import urlopen

# example: python3 mag_test.py -a mag -c sources.50MB -r 10,100,1000 -m 8,32 -q 2 -s 5 -u 4 -k 2

pattern_loc = './patterns'
set_loc = './sets/'
alg_loc = './'

curr_path = os.getcwd()

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

def check_patterns_existance(corpus, m):
	filename = "{}/patterns.{}.{}.bin".format(pattern_loc, corpus, m)
	if os.path.isfile(filename):
		return True
	os.system("python3 generate_patterns.py -c {} -m {}".format(corpus, m))
	

def check_corpus_existance(corpus):
	filename = set_loc + corpus
	if os.path.isfile(filename):
		return True
	if corpus not in pizza_corpus:
		return False
	print("Warning: Corpus does NOT exists. Trying to download (it may take a while).")
	sys.stdout.flush()
	url = pizza_corpus[corpus]
	with urlopen(url) as ret:
		if ret.code != 200:
			return False
	gz_filename = "{}.gz".format(filename)
	with urlopen(url) as response, open(gz_filename, 'wb') as gz_file:
		shutil.copyfileobj(response, gz_file)
	if os.path.isfile(gz_filename):
		with gzip.open(gz_filename, 'rb') as gz_file, open(filename, 'wb') as dest_file:
			dest_file.write(gz_file.read())
		if os.path.isfile(filename):
			os.remove(gz_filename)
			return True
	return False

parser = argparse.ArgumentParser(description='Circullar patter matching script.', 
	epilog="Example:\npython3 test.py -a cpm_faoso_u8_k1,cpm_faoso_u4_k2 -c english.10MB -m 8,32")
parser.add_argument("-a", "--algorithm", dest='a', type=str, default='cpm_mfaoso_u8_k4,cpm_mfaoso_u8_k2,cpm_mfaoso_u8_k1,cpm_mfaoso_u4_k4,cpm_mfaoso_u4_k2,cpm_mfaoso_u4_k1,cpm_faoso_u8_k4,cpm_faoso_u8_k2,cpm_faoso_u8_k1,cpm_faoso_u4_k4,cpm_faoso_u4_k2,cpm_faoso_u4_k1,cpm_mfso_u4,cpm_mfso_u8,cpm_fso_u4,cpm_fso_u8,cpm_mso,cpm_so,cpm_cf', help="algorithm[s] to be tested")
parser.add_argument("-c", "--corpus", dest='c', type=str, default='english.50MB', help="corpus")
parser.add_argument("-m", "--length", dest='m', type=str, default='8,16,32,64', help="pattern length[s] (e.g. 8,16,32)")

args = parser.parse_args()


set_args_list  = args.c.split(',')
a_args_list    = args.a.split(',')
m_args_list    = args.m.split(',')

for c in set_args_list:
	if check_corpus_existance(c) == False:
		print("Error: corpus {} does NOT exists".format(c))
		exit(100)

for c in set_args_list:
	for m in m_args_list:
		check_patterns_existance(c, m)


print ('A\tS\tR\tM\tTime[per_pattern]\tVerCount\tMatches')
for a in a_args_list:
	for s in set_args_list:
		for m in m_args_list:
			proc_filename    = "{}/{}".format(alg_loc, a)
			pattern_filename = "{}/patterns.{}.{}.bin".format(pattern_loc, c, m)
			set_filename     = "{}/{}".format(set_loc, s)
			if not os.path.isfile(proc_filename):
				print ("Error: The prog file not found ( "+proc_filename+")")
				exit()
			if not os.path.isfile(pattern_filename):
				print ("Error: The pattern file not found ( "+pattern_filename+")")
				exit()
			if not os.path.isfile(set_filename):
				print ("Error: The set file not found ( "+set_filename+")")
				exit()
			proc = subprocess.Popen([proc_filename, pattern_filename, m, set_filename], stdout=subprocess.PIPE)
			output = proc.stdout.read().decode('ascii')
			output = "{}\t{}\t{}\t{}".format(a, s, m, output)
			sys.stdout.write(output)
			sys.stdout.flush()
