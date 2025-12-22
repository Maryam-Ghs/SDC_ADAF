build.cblas/syrk.o build.cblas/syrk.d : syrk.cc ../../../cblas.h ../../../interfaces/blas/C/transpose.h \
 ../../../interfaces/blas/C/xerbla.h ../../../ulmblas/ulmblas.h \
 ../../../ulmblas/auxiliary/auxiliary.h ../../../ulmblas/auxiliary/abs1.h \
 ../../../ulmblas/auxiliary/abs1.tcc \
 ../../../ulmblas/auxiliary/conjugate.h \
 ../../../ulmblas/auxiliary/conjugate.tcc \
 ../../../ulmblas/auxiliary/isaligned.h \
 ../../../ulmblas/auxiliary/isaligned.tcc \
 ../../../ulmblas/auxiliary/memorypool.h \
 ../../../ulmblas/auxiliary/memorypool.tcc ../../../ulmblas/config/simd.h \
 ../../../ulmblas/auxiliary/printmatrix.h \
 ../../../ulmblas/auxiliary/printmatrix.tcc \
 ../../../ulmblas/auxiliary/real.h ../../../ulmblas/auxiliary/real.tcc \
 ../../../ulmblas/config/config.h ../../../ulmblas/config/blocksize.h \
 ../../../ulmblas/config/fusefactor.h ../../../ulmblas/level1/level1.h \
 ../../../ulmblas/level1/asum.h ../../../ulmblas/level1/asum.tcc \
 ../../../ulmblas/level1/axpy.h ../../../ulmblas/level1/axpy.tcc \
 ../../../ulmblas/level1/kernel/axpy.h \
 ../../../ulmblas/level1/kernel/ref/axpy.h \
 ../../../ulmblas/level1/kernel/ref/axpy.tcc \
 ../../../ulmblas/level1/copy.h ../../../ulmblas/level1/copy.tcc \
 ../../../ulmblas/level1/dot.h ../../../ulmblas/level1/dot.tcc \
 ../../../ulmblas/level1/kernel/dot.h \
 ../../../ulmblas/level1/kernel/ref/dot.h \
 ../../../ulmblas/level1/kernel/ref/dot.tcc \
 ../../../ulmblas/level1/iamax.h ../../../ulmblas/level1/iamax.tcc \
 ../../../ulmblas/level1/nrm2.h ../../../ulmblas/level1/nrm2.tcc \
 ../../../ulmblas/level1/rot.h ../../../ulmblas/level1/rot.tcc \
 ../../../ulmblas/level1/scal.h ../../../ulmblas/level1/scal.tcc \
 ../../../ulmblas/level1/swap.h ../../../ulmblas/level1/swap.tcc \
 ../../../ulmblas/level1extensions/level1extensions.h \
 ../../../ulmblas/level1extensions/axpy2v.h \
 ../../../ulmblas/level1extensions/axpy2v.tcc \
 ../../../ulmblas/level1extensions/kernel/axpy2v.h \
 ../../../ulmblas/level1extensions/kernel/ref/axpy2v.h \
 ../../../ulmblas/level1extensions/kernel/ref/axpy2v.tcc \
 ../../../ulmblas/level1extensions/axpyf.h \
 ../../../ulmblas/level1extensions/kernel/axpyf.h \
 ../../../ulmblas/level1extensions/kernel/ref/axpyf.h \
 ../../../ulmblas/level1extensions/kernel/ref/axpyf.tcc \
 ../../../ulmblas/level1extensions/axpyf.tcc \
 ../../../ulmblas/level1extensions/dot2v.h \
 ../../../ulmblas/level1extensions/dot2v.tcc \
 ../../../ulmblas/level1extensions/dotaxpy.h \
 ../../../ulmblas/level1extensions/dotaxpy.tcc \
 ../../../ulmblas/level1extensions/kernel/dotaxpy.h \
 ../../../ulmblas/level1extensions/kernel/ref/dotaxpy.h \
 ../../../ulmblas/level1extensions/kernel/ref/dotaxpy.tcc \
 ../../../ulmblas/level1extensions/dotxaxpyf.h \
 ../../../ulmblas/level1extensions/dotxaxpyf.tcc \
 ../../../ulmblas/level1extensions/kernel/dotxaxpyf.h \
 ../../../ulmblas/level1extensions/kernel/ref/dotxaxpyf.h \
 ../../../ulmblas/level1extensions/kernel/ref/dotxaxpyf.tcc \
 ../../../ulmblas/level1extensions/dotxf.h \
 ../../../ulmblas/level1extensions/dotxf.tcc \
 ../../../ulmblas/level1extensions/kernel/dotxf.h \
 ../../../ulmblas/level1extensions/kernel/ref/dotxf.h \
 ../../../ulmblas/level1extensions/kernel/ref/dotxf.tcc \
 ../../../ulmblas/level1extensions/geaxpy.h \
 ../../../ulmblas/level1extensions/geaxpy.tcc \
 ../../../ulmblas/level1extensions/gecopy.h \
 ../../../ulmblas/level1extensions/gecopy.tcc \
 ../../../ulmblas/level1extensions/gescal.h \
 ../../../ulmblas/level1extensions/gescal.tcc \
 ../../../ulmblas/level1extensions/kernel/dot2v.h \
 ../../../ulmblas/level1extensions/kernel/ref/dot2v.h \
 ../../../ulmblas/level1extensions/kernel/ref/dot2v.tcc \
 ../../../ulmblas/level1extensions/kernel/sse/axpy2v.h \
 ../../../ulmblas/level1extensions/kernel/sse/axpy2v.tcc \
 ../../../ulmblas/level1extensions/kernel/sse/axpyf.h \
 ../../../ulmblas/level1extensions/kernel/sse/axpyf.tcc \
 ../../../ulmblas/level1extensions/kernel/sse/dot2v.h \
 ../../../ulmblas/level1extensions/kernel/sse/dot2v.tcc \
 ../../../ulmblas/level1extensions/kernel/sse/dotaxpy.h \
 ../../../ulmblas/level1extensions/kernel/sse/dotaxpy.tcc \
 ../../../ulmblas/level1extensions/kernel/sse/dotxaxpyf.h \
 ../../../ulmblas/level1extensions/kernel/sse/dotxaxpyf.tcc \
 ../../../ulmblas/level1extensions/kernel/sse/dotxf.h \
 ../../../ulmblas/level1extensions/kernel/sse/dotxf.tcc \
 ../../../ulmblas/level1extensions/trlaxpy.h \
 ../../../ulmblas/level1extensions/trlaxpy.tcc \
 ../../../ulmblas/level1extensions/trlscal.h \
 ../../../ulmblas/level1extensions/trlscal.tcc \
 ../../../ulmblas/level1extensions/truaxpy.h \
 ../../../ulmblas/level1extensions/truaxpy.tcc \
 ../../../ulmblas/level1extensions/truscal.h \
 ../../../ulmblas/level1extensions/truscal.tcc \
 ../../../ulmblas/level2/level2.h ../../../ulmblas/level2/gbmtv.h \
 ../../../ulmblas/level2/gbmtv.tcc ../../../ulmblas/level2/gbmv.h \
 ../../../ulmblas/level2/gbmv.tcc ../../../ulmblas/level2/gemv.h \
 ../../../ulmblas/level2/gemv.tcc ../../../ulmblas/level2/ger.h \
 ../../../ulmblas/level2/ger.tcc ../../../ulmblas/level2/hblmv.h \
 ../../../ulmblas/level2/hblmv.tcc ../../../ulmblas/level2/hbumv.h \
 ../../../ulmblas/level2/hbumv.tcc ../../../ulmblas/level2/helmv.h \
 ../../../ulmblas/level2/helmv.tcc ../../../ulmblas/level2/helr.h \
 ../../../ulmblas/level2/helr.tcc ../../../ulmblas/level2/helr2.h \
 ../../../ulmblas/level2/helr2.tcc ../../../ulmblas/level2/hplmv.h \
 ../../../ulmblas/level2/hplmv.tcc ../../../ulmblas/level2/hplr.h \
 ../../../ulmblas/level2/hplr.tcc ../../../ulmblas/level2/hplr2.h \
 ../../../ulmblas/level2/hplr2.tcc ../../../ulmblas/level2/hpumv.h \
 ../../../ulmblas/level2/hpumv.tcc ../../../ulmblas/level2/hpur.h \
 ../../../ulmblas/level2/hpur.tcc ../../../ulmblas/level2/hpur2.h \
 ../../../ulmblas/level2/hpur2.tcc ../../../ulmblas/level2/sblmv.h \
 ../../../ulmblas/level2/sblmv.tcc ../../../ulmblas/level2/sbumv.h \
 ../../../ulmblas/level2/sbumv.tcc ../../../ulmblas/level2/splmv.h \
 ../../../ulmblas/level2/splmv.tcc ../../../ulmblas/level2/splr.h \
 ../../../ulmblas/level2/splr.tcc ../../../ulmblas/level2/splr2.h \
 ../../../ulmblas/level2/splr2.tcc ../../../ulmblas/level2/spumv.h \
 ../../../ulmblas/level2/spumv.tcc ../../../ulmblas/level2/spur.h \
 ../../../ulmblas/level2/spur.tcc ../../../ulmblas/level2/spur2.h \
 ../../../ulmblas/level2/spur2.tcc ../../../ulmblas/level2/sylmv.h \
 ../../../ulmblas/level2/sylmv.tcc ../../../ulmblas/level2/sylr.h \
 ../../../ulmblas/level2/sylr.tcc ../../../ulmblas/level2/sylr2.h \
 ../../../ulmblas/level2/sylr2.tcc ../../../ulmblas/level2/tblmtv.h \
 ../../../ulmblas/level2/tblmtv.tcc ../../../ulmblas/level2/tblmv.h \
 ../../../ulmblas/level2/tblmv.tcc ../../../ulmblas/level2/tblstv.h \
 ../../../ulmblas/level2/tblstv.tcc ../../../ulmblas/level2/tblsv.h \
 ../../../ulmblas/level2/tblsv.tcc ../../../ulmblas/level2/tbumtv.h \
 ../../../ulmblas/level2/tbumtv.tcc ../../../ulmblas/level2/tbumv.h \
 ../../../ulmblas/level2/tbumv.tcc ../../../ulmblas/level2/tbustv.h \
 ../../../ulmblas/level2/tbustv.tcc ../../../ulmblas/level2/tbusv.h \
 ../../../ulmblas/level2/tbusv.tcc ../../../ulmblas/level2/tplmtv.h \
 ../../../ulmblas/level2/tplmtv.tcc ../../../ulmblas/level2/tplmv.h \
 ../../../ulmblas/level2/tplmv.tcc ../../../ulmblas/level2/tplstv.h \
 ../../../ulmblas/level2/tplstv.tcc ../../../ulmblas/level2/tplsv.h \
 ../../../ulmblas/level2/tplsv.tcc ../../../ulmblas/level2/tpumtv.h \
 ../../../ulmblas/level2/tpumtv.tcc ../../../ulmblas/level2/tpumv.h \
 ../../../ulmblas/level2/tpumv.tcc ../../../ulmblas/level2/tpustv.h \
 ../../../ulmblas/level2/tpustv.tcc ../../../ulmblas/level2/tpusv.h \
 ../../../ulmblas/level2/tpusv.tcc ../../../ulmblas/level2/trlmv.h \
 ../../../ulmblas/level2/trlmv.tcc ../../../ulmblas/level2/trlsv.h \
 ../../../ulmblas/level2/trlsv.tcc ../../../ulmblas/level2/trumv.h \
 ../../../ulmblas/level2/trumv.tcc ../../../ulmblas/level2/trusv.h \
 ../../../ulmblas/level2/trusv.tcc ../../../ulmblas/level3/level3.h \
 ../../../ulmblas/level3/gemm.h ../../../ulmblas/level3/gemm.tcc \
 ../../../ulmblas/level3/mkernel/mgemm.h \
 ../../../ulmblas/level3/mkernel/mgemm.tcc \
 ../../../ulmblas/level3/ukernel/ugemm.h \
 ../../../ulmblas/level3/ukernel/ref/ugemm.h \
 ../../../ulmblas/level3/ukernel/ref/ugemm.tcc \
 ../../../ulmblas/level3/ukernel/ugemm.tcc \
 ../../../ulmblas/level3/pack/gepack.h \
 ../../../ulmblas/level3/pack/gepack.tcc ../../../ulmblas/level3/helmm.h \
 ../../../ulmblas/level3/helmm.tcc ../../../ulmblas/level3/pack/helpack.h \
 ../../../ulmblas/level3/pack/helpack.tcc \
 ../../../ulmblas/level3/helr2k.h ../../../ulmblas/level3/helr2k.tcc \
 ../../../ulmblas/level3/mkernel/msylrk.h \
 ../../../ulmblas/level3/mkernel/msylrk.tcc \
 ../../../ulmblas/level3/ukernel/usylrk.h \
 ../../../ulmblas/level3/ukernel/usylrk.tcc \
 ../../../ulmblas/level3/helrk.h ../../../ulmblas/level3/helrk.tcc \
 ../../../ulmblas/level3/heumm.h ../../../ulmblas/level3/heumm.tcc \
 ../../../ulmblas/level3/pack/heupack.h \
 ../../../ulmblas/level3/pack/heupack.tcc \
 ../../../ulmblas/level3/heur2k.h ../../../ulmblas/level3/heur2k.tcc \
 ../../../ulmblas/level3/mkernel/msyurk.h \
 ../../../ulmblas/level3/mkernel/msyurk.tcc \
 ../../../ulmblas/level3/ukernel/usyurk.h \
 ../../../ulmblas/level3/ukernel/usyurk.tcc \
 ../../../ulmblas/level3/heurk.h ../../../ulmblas/level3/heurk.tcc \
 ../../../ulmblas/level3/mkernel/mtrlmm.h \
 ../../../ulmblas/level3/mkernel/mtrlmm.tcc \
 ../../../ulmblas/level3/mkernel/mtrlsm.h \
 ../../../ulmblas/level3/mkernel/mtrlsm.tcc \
 ../../../ulmblas/level3/ukernel/utrlsm.h \
 ../../../ulmblas/level3/ukernel/utrlsm.tcc \
 ../../../ulmblas/level3/ukernel/ref/utrlsm.h \
 ../../../ulmblas/level3/ukernel/ref/utrlsm.tcc \
 ../../../ulmblas/level3/mkernel/mtrumm.h \
 ../../../ulmblas/level3/mkernel/mtrumm.tcc \
 ../../../ulmblas/level3/mkernel/mtrusm.h \
 ../../../ulmblas/level3/mkernel/mtrusm.tcc \
 ../../../ulmblas/level3/ukernel/utrusm.h \
 ../../../ulmblas/level3/ukernel/utrusm.tcc \
 ../../../ulmblas/level3/ukernel/ref/utrusm.h \
 ../../../ulmblas/level3/ukernel/ref/utrusm.tcc \
 ../../../ulmblas/level3/pack/sylpack.h \
 ../../../ulmblas/level3/pack/sylpack.tcc \
 ../../../ulmblas/level3/pack/syupack.h \
 ../../../ulmblas/level3/pack/syupack.tcc \
 ../../../ulmblas/level3/pack/trlpack.h \
 ../../../ulmblas/level3/pack/trlpack.tcc \
 ../../../ulmblas/level3/pack/trlspack.h \
 ../../../ulmblas/level3/pack/trlspack.tcc \
 ../../../ulmblas/level3/pack/trupack.h \
 ../../../ulmblas/level3/pack/trupack.tcc \
 ../../../ulmblas/level3/pack/truspack.h \
 ../../../ulmblas/level3/pack/truspack.tcc \
 ../../../ulmblas/level3/sylmm.h ../../../ulmblas/level3/sylmm.tcc \
 ../../../ulmblas/level3/sylr2k.h ../../../ulmblas/level3/sylr2k.tcc \
 ../../../ulmblas/level3/sylrk.h ../../../ulmblas/level3/sylrk.tcc \
 ../../../ulmblas/level3/syumm.h ../../../ulmblas/level3/syumm.tcc \
 ../../../ulmblas/level3/syur2k.h ../../../ulmblas/level3/syur2k.tcc \
 ../../../ulmblas/level3/syurk.h ../../../ulmblas/level3/syurk.tcc \
 ../../../ulmblas/level3/trlmm.h ../../../ulmblas/level3/trlmm.tcc \
 ../../../ulmblas/level3/trlsm.h ../../../ulmblas/level3/trlsm.tcc \
 ../../../ulmblas/level3/trumm.h ../../../ulmblas/level3/trumm.tcc \
 ../../../ulmblas/level3/trusm.h ../../../ulmblas/level3/trusm.tcc \
 ../../../ulmblas/level3/ukernel/sse/ugemm.h \
 ../../../ulmblas/level3/ukernel/sse/ugemm.tcc \
 ../../../ulmblas/level3/ukernel/sse/utrlsm.h \
 ../../../ulmblas/level3/ukernel/sse/utrlsm.tcc \
 ../../../ulmblas/level3/ukernel/sse/utrusm.h \
 ../../../ulmblas/level3/ukernel/sse/utrusm.tcc
