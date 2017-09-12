import subprocess, sys, os

# Full test
# python test.py cpm_cf.exe,cpm_so.exe,cpm_mso.exe,cpm_fso_u4.exe,cpm_fso_u8.exe,cpm_mfso_u4.exe,cpm_mfso_u8.exe,cpm_faoso_u8_k4.exe,cpm_faoso_u8_k2.exe,cpm_faoso_u8_k1.exe,cpm_faoso_u4_k4.exe,cpm_faoso_u4_k2.exe,cpm_faoso_u4_k1.exe,cpm_mfaoso_u8_k4.exe,cpm_mfaoso_u8_k2.exe,cpm_mfaoso_u8_k1.exe,cpm_mfaoso_u4_k4.exe,cpm_mfaoso_u4_k2.exe,cpm_mfaoso_u4_k1.exe, english.200MB 10 8,16,32,64

# Windows
pattern_loc = 'Y:/CPM/patterns' # each folder should have name with suffix r1000 where 1000 is number of patterns
set_loc     = 'Y:/CPM/sets'
alg_loc     = 'Z:/2013-circular_pattern_matching/source/github'

args_num = len(sys.argv) - 1

if sys.argv[1]=='--help':
	print ('Circullar patter matching tester help.')
	print ('')
	print ('Syntax:')
	print ('test [--help] algorithm test_set m')
	print ('')
	print ('--help      Shows the help')
	print ('algorithm   Algorithm(eg. cf,fso)')
	print ('test_set    Test set(eg. english.100MB)')
	print ('r           Pattern number(eg. 1000)')
	print ('m           Pattern length(eg. 8)')
	print ('')
	print ('Example:')
	print ('python test.py cpm_fso,cpm_mfso english.200MB 10 16,32')
	print ('')
	exit()

# Error
if args_num < 4:
    print ("Error not enought parameters. See --help.")
    exit()

# algorithm
algs      = sys.argv[1] # algorithms
# arguments:
set_args  = sys.argv[2] # test text sets
r_args    = sys.argv[3] # 
m_args    = sys.argv[4] # pattern length

set_args_list  = set_args.split(',')
a_args_list    = algs.split(',')
r_args_list    = r_args.split(',')
m_args_list    = m_args.split(',')

print ('A\t' + 'S\t' + 'R\t' + 'M\t' + 'Time[per_pattern]\t' + 'VerCount\t' + 'Matches')
for a in a_args_list:
	for s in set_args_list:
		for r in r_args_list:
			for m in m_args_list:
				proc_filename    = alg_loc + '/' + a 
				pattern_filename = pattern_loc + '.r' + r + '/patterns.' + s + '.' + m + '.bin'
				set_filename     = set_loc + '/' + s
				if not os.path.isfile(proc_filename):
					print ("Error: The prog file not found ( "+proc_filename+")")
					exit()
				if not os.path.isfile(pattern_filename):
					print ("Error: The pattern file not found ( "+pattern_filename+")")
					exit()
				if not os.path.isfile(set_filename):
					print ("Error: The set file not found ( "+set_filename+")")
					exit()
				#print proc_filename, pattern_filename, m, set_filename, u, k, q
				proc = subprocess.Popen([proc_filename, pattern_filename, m, set_filename], stdout=subprocess.PIPE)
				output = proc.stdout.read().decode('ascii')
				output = a + '\t' + s + '\t' + str(r) + '\t' + str(m) + '\t' + output;
				sys.stdout.write(output)
				sys.stdout.flush()
