VISUAL_FLAGS=/GS /GL /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Zc:inline /fp:precise /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /WX- /Zc:forScope /Gd /Oi /MD /EHsc /Ot

cpm_cf: cpm_cf.cpp headers.h
	cl $(VISUAL_FLAGS) cpm_cf.cpp /link /out:cpm_cf.exe

cpm_so: cpm_so.cpp headers.h
	cl $(VISUAL_FLAGS) cpm_so.cpp /link /out:cpm_so.exe

cpm_mso: cpm_mso.cpp headers.h
	cl $(VISUAL_FLAGS) cpm_mso.cpp /link /out:cpm_mso.exe

cpm_fso_u4: cpm_fso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 cpm_fso.cpp /link /out:cpm_fso_u4.exe

cpm_fso_u8: cpm_fso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 cpm_fso.cpp /link /out:cpm_fso_u8.exe

cpm_fso: cpm_fso_u4 cpm_fso_u8

cpm_mfso_u4: cpm_mfso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 cpm_mfso.cpp /link /out:cpm_mfso_u4.exe

cpm_mfso_u8: cpm_mfso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 cpm_mfso.cpp /link /out:cpm_mfso_u8.exe

cpm_mfso: cpm_mfso_u4 cpm_mfso_u8

cpm_faoso_u8_k4: cpm_faoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 /DK_PARAM=4 cpm_faoso.cpp /link /out:cpm_faoso_u8_k4.exe

cpm_faoso_u8_k2: cpm_faoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 /DK_PARAM=2 cpm_faoso.cpp /link /out:cpm_faoso_u8_k2.exe

cpm_faoso_u8_k1: cpm_faoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 /DK_PARAM=1 cpm_faoso.cpp /link /out:cpm_faoso_u8_k1.exe

cpm_faoso_u4_k4: cpm_faoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 /DK_PARAM=4 cpm_faoso.cpp /link /out:cpm_faoso_u4_k4.exe

cpm_faoso_u4_k2: cpm_faoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 /DK_PARAM=2 cpm_faoso.cpp /link /out:cpm_faoso_u4_k2.exe

cpm_faoso_u4_k1: cpm_faoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 /DK_PARAM=1 cpm_faoso.cpp /link /out:cpm_faoso_u4_k1.exe

cpm_faoso: cpm_faoso_u8_k4 cpm_faoso_u8_k2 cpm_faoso_u8_k1 cpm_faoso_u4_k4 cpm_faoso_u4_k2 cpm_faoso_u4_k1

cpm_mfaoso_u8_k4: cpm_mfaoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 /DK_PARAM=4 cpm_mfaoso.cpp /link /out:cpm_mfaoso_u8_k4.exe

cpm_mfaoso_u8_k2: cpm_mfaoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 /DK_PARAM=2 cpm_mfaoso.cpp /link /out:cpm_mfaoso_u8_k2.exe

cpm_mfaoso_u8_k1: cpm_mfaoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=8 /DK_PARAM=1 cpm_mfaoso.cpp /link /out:cpm_mfaoso_u8_k1.exe

cpm_mfaoso_u4_k4: cpm_mfaoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 /DK_PARAM=4 cpm_mfaoso.cpp /link /out:cpm_mfaoso_u4_k4.exe

cpm_mfaoso_u4_k2: cpm_mfaoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 /DK_PARAM=2 cpm_mfaoso.cpp /link /out:cpm_mfaoso_u4_k2.exe

cpm_mfaoso_u4_k1: cpm_mfaoso.cpp headers.h
	cl $(VISUAL_FLAGS) /DU_PARAM=4 /DK_PARAM=1 cpm_mfaoso.cpp /link /out:cpm_mfaoso_u4_k1.exe
	
cpm_mfaoso: cpm_mfaoso_u8_k4 cpm_mfaoso_u8_k2 cpm_mfaoso_u8_k1 cpm_mfaoso_u4_k4 cpm_mfaoso_u4_k2 cpm_mfaoso_u4_k1

all: cpm_cf cpm_so cpm_mso cpm_fso cpm_mfso cpm_faoso cpm_mfaoso

clean:
	del *.exe *.pdb *.obj

