TESTS = test_snd_pink_diffuse test_ir1 test_ir2 test_ir3 test_ir4			\
	test_ir6_ismminmax test_snd1 test_snd_include_sound test_snd2				\
	test_snd4 test_snd3 test_snd5 test_pos1 test_pos2										\
	test_pos_trackinterp test_snd_door1 test_snd_door2 test_snd_door3		\
	test_pos_door test_snd_layers test_snd_rec_amb1h1v test_wav_diffuse	\
	test_wav_diffuse_hoa2d test_ir_hoa2d_offset test_wav_diffuse_nsp4		\
	test_wav_diffuse_hoa2d4 test_wav_diffuse_layerbug test_wav_diffirs	\
	test_sndgainramp test_sndgainramp2 test_ir_spkcorr test_snd_calib1	\
	test_snd_calib2 test_snd_vbap51 test_snd_pink test_snd_sndfile			\
	test_snd_sndfile2 test_snd_door4 test_snd_roommic test_level_vbap3d	\
	test_ir_ortf_0deg test_ir_ortf_55deg test_ir_scatter								\
	test_ir_noscatter test_ir_scatter_ortf test_snd_sourcedir_generic		\
	test_snd_sourcedir_generic1 test_snd_sourcedir_generic_cardioid			\
	test_ir_wfs test_ir_wfs_noplanewave hoa3d test_level_hoa2d_basic		\
	test_level_hoa2d_maxre test_ir_reverb test_ir_simplefdn							\
	test_ir_simplefdn_gain test_snd_vbap3d_speakermatch									\
	test_ir_volumetric test_pos_obstacle test_pos_obstacle_inner				\
	test_level_absorption test_ir_hrtf_0deg test_ir_hrtf_45deg					\
	test_ir_hrtf_75deg test_ir_hrtf_90deg test_ir_hrtf_105deg						\
	test_ir_hrtf_135deg test_ir_hrtf_180deg test_ir_hrtf_225deg					\
	test_ir_hrtf_270deg test_ir_hrtf_315deg test_ir_hrtf_el90deg				\
	test_ir_hrtf_el-90deg test_ir_hrtf_el45deg test_ir_hrtf_el-45deg		\
	test_ir_hrtf_diffuse1 test_ir_hrtf_diffuse2 test_ir_delay						\
	test_ir_delay2 test_ir_delay3 test_snd_reverb test_wav_multichannel	\
	test_snd_zeros test_ir_sub test_ir_sub_hoa2d test_ir_sub_nsp				\
	test_ir_partconvrev test_ir_partconvrev_offset											\
	test_ir_micarray_az0deg test_ir_micarray_az45deg										\
	test_ir_micarray_az75deg test_ir_micarray_az90deg										\
	test_ir_micarray_az105deg test_ir_micarray_az135deg									\
	test_ir_micarray_az180deg test_ir_micarray_az225deg									\
	test_ir_micarray_az270deg test_ir_micarray_az315deg									\
	test_ir_micarray_el45deg test_ir_micarray_el90deg										\
	test_ir_micarray_el-45deg test_ir_micarray_el-90deg									\
	test_snd_diffuse_micarray test_snd_micarray_az0deg									\
	test_ir_micarraysinc test_ir_amb1 test_ir_amb1_y test_ir_amb1_z			\
	test_snd_diffuse_0deg test_snd_diffuse_17deg												\
	test_snd_diffuse_rec17deg test_snd_maskplugin_fig8									\
	test_snd_maskplugin_multibeam test_snd_maskplugin_multibeam1				\
	test_snd_diffuse_inphase test_snd_diffuse_basic											\
	test_snd_diffuse_maxre test_snd_maskplugin_multibeam_diff						\
	test_ir_apfilter_highpass test_ir_apfilter_lowpass

#test_ir_simplefdn_optimt60

TEST_FAIL = test_fail_vbap3d_flat test_notfail_vbap3d_3d	\
	test_fail_duplicatenames test_fail_duplicatescenenames	\
	test_fail_ir_micarray test_fail_hoa2d_nonflat		\
	test_fail_hoa2d_irregular test_fail_invalidmaskplugin

TEST_JACK = jack_routeplugin test_unload_on_error			\
	jackfail_connectfail jack_connect jack_hoafdnrot		\
	jackconnect_ortf jackconnect_amb1h1v jackconnect_hoa2dfuma

TEST_SND=$(wildcard test_snd*.tsc)


RECEIVERS = omni nsp amb3h0v amb3h3v amb1h0v amb1h1v cardioid hann	\
  vbap hoa2d ortf intensityvector vmic chmap hoa2d_fuma cardioidmod	\
  debugpos hoa2d_fuma_hos wfs hrtf micarray



LEVELREC = nsp hoa2d wfs vbap hann

LEVTHR=0.25
IRLEN = 4000

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
LIBVAR=LD_LIBRARY_PATH
endif
ifeq ($(UNAME_S),Darwin)
LIBVAR=DYLD_LIBRARY_PATH
endif
LIBPATH=$(LIBVAR)=../libtascar/build/:../plugins/build/
VALIDATE=../apps/build/tascar_validatetsc
RENDERIR=../apps/build/tascar_renderir
RENDERFILE=../apps/build/tascar_renderfile
TASCARCLI=../apps/build/tascar_cli
JACKLSP=../apps/build/tascar_lsjackp
JACKIO=../apps/build/tascar_jackio
COMPARE=../apps/build/tascar_test_compare_sndfile
COMPLEV=../apps/build/tascar_test_compare_level_sum

TEST_REC = $(patsubst %,test_rec_%,$(RECEIVERS))
TEST_LEV = $(patsubst %,test_reclevel_%,$(LEVELREC))

FAILING_TESTS = test_ir5

TOL = 2e-7
RMSTOL = 2e-7

all: $(TESTS) $(TEST_FAIL) testrec testlev

jack: $(TEST_JACK)

test_reclevel_wfs test_reclevel_vbap test_reclevel_hann: LEVTHR=2.5
test_level_vbap3d_lidhan45sub: LEVTHR=3
test_level_diff_decorr: LEVTHR=1.5

#test_level_hoa3d_allrad: LEVTHR=2.7

ifeq ($(UNAME_S),Linux)
hoa3d: test_snd_hoa3d_enc_hor test_snd_hoa3d_enc_vert			\
  test_snd_hoa3d_pinv_hor test_snd_hoa3d_pinv_vert			\
  test_snd_hoa3d_allrad_hor test_snd_hoa3d_allrad_vert			\
  test_level_hoa3d_pinv test_level_hoa3d_pinv_lidhan			\
  test_level_hoa3d_pinv_maxre test_level_hoa3d_allrad			\
  test_level_hoa3d_allrad_lidhan test_level_hoa3d_pinv_lidhan_maxre	\
  test_level_hoa3d_pinv_lidhan45_maxre					\
  test_level_hoa3d_pinv_lidhan45sub_maxre
else
hoa3d: test_snd_hoa3d_enc_hor test_snd_hoa3d_enc_vert			\
  test_snd_hoa3d_pinv_hor test_snd_hoa3d_pinv_vert			\
  test_level_hoa3d_pinv test_level_hoa3d_pinv_lidhan			\
  test_level_hoa3d_pinv_maxre test_level_hoa3d_allrad			\
  test_level_hoa3d_allrad_lidhan test_level_hoa3d_pinv_lidhan_maxre	\
  test_level_hoa3d_pinv_lidhan45_maxre					\
  test_level_hoa3d_pinv_lidhan45sub_maxre
endif

testrec: $(TEST_REC)

testlev: $(TEST_LEV) test_level_diff_decorr test_level_diff_nodecorr	\
  test_level_hoa2d_basic test_level_hoa2d_maxre				\
  test_level_hoa3d_allrad_lidhan test_level_hoa3d_allrad		\
  test_level_hoa3d_pinv_lidhan_maxre test_level_hoa3d_pinv_lidhan	\
  test_level_hoa3d_pinv_maxre test_level_hoa3d_pinv test_level_nsp	\
  test_level_vbap3d test_level_hoa3d_pinv_lidhan45_maxre		\
  test_level_hoa3d_pinv_lidhan45sub_maxre				\
  test_level_vbap3d_lidhan45sub


db: $(TEST:test=db_test)  $(TEST_REC:test=db_test)

test_ir%: test_ir%.tsc expected_ir%.wav
	@echo "Impulse response test: $<"
	@$(LIBPATH) $(VALIDATE) $< || (echo "$(<):2: Validation failed"; false)
	@$(LIBPATH) $(RENDERIR) -o test_ir$*.wav $< -t 1 -l $(IRLEN) -f 44100 || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPARE) expected_ir$*.wav test_ir$*.wav $(TOL) $(RMSTOL) || (echo "$(<):2: Output differs"; false)
	@rm -f test_ir$*.wav

test_wav%: test_wav%.tsc input_wav%.wav expected_wav%.wav
	@echo "Input-output processing test: $<"
	@$(LIBPATH) $(VALIDATE) $< || (echo "$(<):2: Validation failed"; false)
	@$(LIBPATH) $(RENDERFILE) -i input_wav$*.wav -f 64 -o test_wav$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPARE) expected_wav$*.wav test_wav$*.wav $(TOL) $(RMSTOL) || (echo "$(<):2: Output differs"; false)
	@rm -f test_wav$*.wav

test_snd%: test_snd%.tsc expected_snd%.wav
	@echo "Generation test: $<"
	@$(LIBPATH) $(VALIDATE) $< || (echo "$(<):2: Validation failed"; false)
	@$(LIBPATH) $(RENDERFILE) -i zeros.wav -f 64 -o test_snd$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPARE) expected_snd$*.wav test_snd$*.wav $(TOL) $(RMSTOL) || (echo "$(<):2: Output differs"; false)
#	@rm -f test_snd$*.wav

test_pos%: test_pos%.tsc expected_pos%.wav
	@echo "Position test: $<"
	@$(LIBPATH) RECTYPE=debugpos $(VALIDATE) $< || (echo "$(<):2: Validation failed"; false)
	@$(LIBPATH) RECTYPE=debugpos $(RENDERFILE) -i zeros.wav -f 64 -o test_pos$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPARE) expected_pos$*.wav test_pos$*.wav 1e-7 1e-7|| (echo "$(<):2: Output differs"; false)
	@rm -f test_pos$*.wav

test_rec_%: test_rec.tsc
	@echo "Receiver test: $< ($*)"
	@$(LIBPATH) RECEIVER=$* $(RENDERFILE) -i zeros.wav -f 64 -o test_rec_$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@rm -f test_rec_$*.wav

test_reclevel_%: test_level.tsc
	@echo "Receiver level test: $< ($*)"
	@$(LIBPATH) RECEIVER=$* CHANNELS=8 $(RENDERFILE) -i zeros.wav -f 64 -o test_level_$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPLEV) 70 test_level_$*.wav $(LEVTHR) || (echo "$(<):2: Level differs (8ch)"; false)
	@$(LIBPATH) RECEIVER=$* CHANNELS=36 $(RENDERFILE) -i zeros.wav -f 64 -o test_level_$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPLEV) 70 test_level_$*.wav $(LEVTHR) || (echo "$(<):2: Level differs (36ch)"; false)
	@rm -f test_level_$*.wav

test_level_%: test_level_%.tsc
	@echo "Level test: $< ($*)"
	@$(LIBPATH) $(VALIDATE) $< || (echo "$(<):2: Validation failed"; false)
	@$(LIBPATH) RECEIVER=$* $(RENDERFILE) -i zeros.wav -f 64 -o test_level_$*.wav $< || (echo "$(<):2: Rendering failed"; false)
	@$(LIBPATH) $(COMPLEV) 70 test_level_$*.wav $(LEVTHR) || (echo "$(<):2: Level differs"; false)
	@rm -f test_level_$*.wav


test_fail_%: fail_%.tsc
	@echo "Failure test: $< ($*)"
	@(! $(LIBPATH) $(RENDERFILE) -i zeros.wav -f 64 -o test_fail.wav $< ) || (echo "$(<):2: Did not fail"; false)
	@rm -f test_fail.wav

test_notfail_%: notfail_%.tsc
	@echo "No failure test: $< ($*)"
	@$(LIBPATH) $(RENDERFILE) -i zeros.wav -f 64 -o test_fail.wav $< || (echo "$(<):2: Failed."; false)
	@rm -f test_fail.wav


# debugging rules:

db_test_wav%: test_wav%.tsc input_wav%.wav expected_wav%.wav
	$(LIBPATH) $(VALIDATE) $< 
	echo run -i input_wav$*.wav -f 64 -o test_wav$*.wav $< > gdbcmd
	$(LIBPATH) gdb $(RENDERFILE) -x gdbcmd
	$(LIBPATH) $(COMPARE) expected_wav$*.wav test_wav$*.wav 2e-8
	rm -f test_wav$*.wav

db_test_level_%: test_level_%.tsc
	@echo "Level test: $< ($*)"
	echo run -i zeros.wav -f 64 -o test_level_$*.wav $< > gdbcmd
	$(LIBPATH) gdb $(RENDERFILE) -x gdbcmd
	@rm -f test_level_$*.wav

db_test_rec_%: test_rec.tsc
	echo run -i zeros.wav -f 64 -o test_rec_$*.wav $< > gdbcmd
	$(LIBPATH) RECEIVER=$* gdb $(RENDERIR) -x gdbcmd
	rm -f test_rec_$*.wav

db_test_ir%: test_ir%.tsc expected_ir%.wav
	echo run -o test_ir$*.wav $< -t 1 -l $(IRLEN) -f 44100 > gdbcmd
	$(LIBPATH) gdb $(RENDERIR) -x gdbcmd
	$(LIBPATH) $(COMPARE) expected_ir$*.wav test_ir$*.wav 1e-9 1e-9
	rm -f test_ir$*.wav

db_test_snd%: test_snd%.tsc expected_snd%.wav
	echo run -i zeros.wav -o test_snd$*.wav -f 64 $< > gdbcmd
	$(LIBPATH) gdb $(RENDERFILE) -x gdbcmd
	$(LIBPATH) $(COMPARE) expected_snd$*.wav test_snd$*.wav 1e-9 1e-9
	rm -f test_snd$*.wav

db_test_pos%: test_pos%.tsc expected_pos%.wav
	echo run -i zeros.wav -o test_pos$*.wav -f 64 $< > gdbcmd
	$(LIBPATH) gdb $(RENDERFILE) -x gdbcmd
	$(LIBPATH) ../build/compare_posfile expected_pos$*.wav test_pos$*.wav 1e-9 1e-9
	rm -f test_pos$*.wav

leak_test_snd%: test_snd%.tsc expected_snd%.wav
	$(LIBPATH) valgrind --leak-check=full $(RENDERFILE) -i zeros.wav -o test_snd$*.wav -f 64 $<
	$(LIBPATH) $(COMPARE) expected_snd$*.wav test_snd$*.wav 1e-9 1e-9
	rm -f test_snd$*.wav

leak_test_pos%: test_pos%.tsc expected_pos%.wav
	$(LIBPATH) valgrind --leak-check=full $(RENDERIR) -i zeros.wav -o test_pos$*.wav -f 64 $<
	$(LIBPATH) ../build/compare_posfile expected_pos$*.wav test_pos$*.wav 1e-9
	rm -f test_pos$*.wav

leak_%: %.tsc
	$(LIBPATH) valgrind --leak-check=full  --show-leak-kinds=all $(RENDERFILE) -i zeros.wav -o $*.wav -f 64 $<

valgrind_%: %.tsc
	$(LIBPATH) valgrind  $(RENDERFILE) -i zeros.wav -o $*.wav -f 64 $<


all_init: $(patsubst %,init_%,$(TESTS))

init_%: %.tsc
	$(LIBPATH) valgrind --error-exitcode=1 --leak-check=no --undef-value-errors=yes --track-origins=yes $(RENDERFILE) -i zeros.wav -o $*.wav -f 64 $<

init_test_ir%: test_ir%.tsc
	$(LIBPATH) valgrind --error-exitcode=1 --leak-check=no --undef-value-errors=yes --track-origins=yes $(RENDERIR) -o test_ir$*.wav $< -t 1 -l $(IRLEN) -f 44100

clean:
	rm -f *~ test*.wav gdbcmd

test_unload_on_error: test_unload_on_error.tsc
	@sleep 1
	rm -f test_unload_on_error.loaded test_unload_on_error.unloaded
	jackd -d dummy & PID=$$!; sleep 1;$(LIBPATH) $(TASCARCLI) $< ; kill -9 $$PID
	test -e test_unload_on_error.loaded || (echo "load failed."; false)
	rm -f test_unload_on_error.loaded
	test -e test_unload_on_error.unloaded || (echo "unload failed."; false)
	rm -f test_unload_on_error.unloaded
	@sleep 1

jack_%: test_%.tsc input_%.wav expected_%.wav
	@$(LIBPATH) $(VALIDATE) $< || (echo "$(<):2: Validation failed"; false)
	@sleep 1
	@jackd -d dummy -r 44100 -p 1024 & JACKPID=$$!; sleep 1;$(LIBPATH) $(TASCARCLI) -s $< & TSCPID=$$!; sleep 1;echo "input: " `$(LIBPATH) $(JACKLSP) -si|grep -v -e '.*:sync_in'`;echo "output: " `$(LIBPATH) $(JACKLSP) -so|grep -v -e '.*:sync_out'` ; $(LIBPATH) $(JACKIO) -s 0 input_$*.wav -o test_$*.wav `$(LIBPATH) $(JACKLSP) -si|grep -v -e '.*:sync_in'` `$(LIBPATH) $(JACKLSP) -so|grep -v -e '.*:sync_out'`; kill -9 $$JACKPID $$TSCPID; true
	@$(LIBPATH) $(COMPARE) expected_$*.wav test_$*.wav $(TOL) $(RMSTOL) || (echo "$(<):2: Output differs"; false)
	@sleep 1

jackfail_%: test_%.tsc
	@sleep 1
	TSCRET=ok; jackd -d dummy -r 44100 -p 1024 & JACKPID=$$!; sleep 1;$(LIBPATH) $(TASCARCLI) -s $< & TSCPID=$$!; sleep 1;ps $$TSCPID > /dev/null || TSCRET=fail; kill -9 $$JACKPID $$TSCPID; test $$TSCRET = fail || (echo "$(<):2: Did not fail."; false)
	@sleep 1

jackconnect_%: test_connect%.tsc
	@sleep 1
	TSCRET=ok; jackd -d dummy -r 44100 -p 1024 & JACKPID=$$!; sleep 1;$(LIBPATH) $(TASCARCLI) -s $< & TSCPID=$$!; sleep 1;ps $$TSCPID > /dev/null || TSCRET=fail; kill -9 $$JACKPID $$TSCPID 2>/dev/null ; test $$TSCRET = ok || (echo "$(<):2: Connection failed."; false)
	@sleep 1


test_snd_hoa3d_enc_hor test_snd_hoa3d_enc_vert test_snd_hoa3d_pinv_hor test_snd_hoa3d_allrad_hor test_snd_hoa3d_allrad_vert test_snd_hoa3d_pinv_vert: TOL=4e-4
test_snd_hoa3d_enc_hor test_snd_hoa3d_enc_vert test_snd_hoa3d_pinv_hor test_snd_hoa3d_allrad_hor test_snd_hoa3d_allrad_vert test_snd_hoa3d_pinv_vert: RMSTOL=1e-4
test_ir_simplefdn test_ir_simplefdn_gain test_ir_simplefdn_optimt60: IRLEN=44100
test_ir_reverb: IRLEN=44100
test_ir_partconvrev: IRLEN=44100
test_ir_partconvrev_offset: IRLEN=44100
test_ir_temp: IRLEN=441000
test_ir_volumetric: TOL=1e-5
test_ir_sub: TOL=1e-6
test_ir_sub_hoa2d: TOL=1e-6
test_ir_sub_nsp: TOL=1e-6
test_ir_apfilter_highpass: TOL=1e-6
test_ir_apfilter_lowpass: TOL=1e-6
test_snd_vbap3d_speakermatch: TOL=1e-5
test_snd_vbap3d_speakermatch: RMSTOL=1e-6
test_snd_sndfile: TOL=3e-7
test_snd_reverb: TOL=1e-5
test_snd_reverb: RMSTOL=1e-6
test_snd_maskplugin_multibeam: RMSTOL=1e-6
test_snd_maskplugin_multibeam: TOL=1e-5
test_snd_maskplugin_multibeam1: TOL=1e-5
test_snd_maskplugin_fig8: TOL=1e-5

%.octave: %.m
	octave --no-gui --eval $*

%.matlab: %.m
	matlab -nodisplay -batch $*
