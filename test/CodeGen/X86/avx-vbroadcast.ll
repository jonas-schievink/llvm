; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-apple-darwin -mcpu=corei7-avx -mattr=+avx | FileCheck %s

define <4 x i64> @A(i64* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: A:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastsd (%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %q = load i64, i64* %ptr, align 8
  %vecinit.i = insertelement <4 x i64> undef, i64 %q, i32 0
  %vecinit2.i = insertelement <4 x i64> %vecinit.i, i64 %q, i32 1
  %vecinit4.i = insertelement <4 x i64> %vecinit2.i, i64 %q, i32 2
  %vecinit6.i = insertelement <4 x i64> %vecinit4.i, i64 %q, i32 3
  ret <4 x i64> %vecinit6.i
}

define <8 x i32> @B(i32* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: B:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss (%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %q = load i32, i32* %ptr, align 4
  %vecinit.i = insertelement <8 x i32> undef, i32 %q, i32 0
  %vecinit2.i = insertelement <8 x i32> %vecinit.i, i32 %q, i32 1
  %vecinit4.i = insertelement <8 x i32> %vecinit2.i, i32 %q, i32 2
  %vecinit6.i = insertelement <8 x i32> %vecinit4.i, i32 %q, i32 3
  ret <8 x i32> %vecinit6.i
}

define <4 x double> @C(double* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: C:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastsd (%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %q = load double, double* %ptr, align 8
  %vecinit.i = insertelement <4 x double> undef, double %q, i32 0
  %vecinit2.i = insertelement <4 x double> %vecinit.i, double %q, i32 1
  %vecinit4.i = insertelement <4 x double> %vecinit2.i, double %q, i32 2
  %vecinit6.i = insertelement <4 x double> %vecinit4.i, double %q, i32 3
  ret <4 x double> %vecinit6.i
}

define <8 x float> @D(float* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: D:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss (%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %q = load float, float* %ptr, align 4
  %vecinit.i = insertelement <8 x float> undef, float %q, i32 0
  %vecinit2.i = insertelement <8 x float> %vecinit.i, float %q, i32 1
  %vecinit4.i = insertelement <8 x float> %vecinit2.i, float %q, i32 2
  %vecinit6.i = insertelement <8 x float> %vecinit4.i, float %q, i32 3
  ret <8 x float> %vecinit6.i
}

;;;; 128-bit versions

define <4 x float> @e(float* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: e:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss (%rdi), %xmm0
; CHECK-NEXT:    retq
entry:
  %q = load float, float* %ptr, align 4
  %vecinit.i = insertelement <4 x float> undef, float %q, i32 0
  %vecinit2.i = insertelement <4 x float> %vecinit.i, float %q, i32 1
  %vecinit4.i = insertelement <4 x float> %vecinit2.i, float %q, i32 2
  %vecinit6.i = insertelement <4 x float> %vecinit4.i, float %q, i32 3
  ret <4 x float> %vecinit6.i
}

; Don't broadcast constants on pre-AVX2 hardware.
define <4 x float> @_e2(float* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: _e2:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovaps {{.*#+}} xmm0 = [-7.812500e-03,-7.812500e-03,-7.812500e-03,-7.812500e-03]
; CHECK-NEXT:    retq
entry:
   %vecinit.i = insertelement <4 x float> undef, float       0xbf80000000000000, i32 0
  %vecinit2.i = insertelement <4 x float> %vecinit.i, float  0xbf80000000000000, i32 1
  %vecinit4.i = insertelement <4 x float> %vecinit2.i, float 0xbf80000000000000, i32 2
  %vecinit6.i = insertelement <4 x float> %vecinit4.i, float 0xbf80000000000000, i32 3
  ret <4 x float> %vecinit6.i
}


define <4 x i32> @F(i32* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: F:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss (%rdi), %xmm0
; CHECK-NEXT:    retq
entry:
  %q = load i32, i32* %ptr, align 4
  %vecinit.i = insertelement <4 x i32> undef, i32 %q, i32 0
  %vecinit2.i = insertelement <4 x i32> %vecinit.i, i32 %q, i32 1
  %vecinit4.i = insertelement <4 x i32> %vecinit2.i, i32 %q, i32 2
  %vecinit6.i = insertelement <4 x i32> %vecinit4.i, i32 %q, i32 3
  ret <4 x i32> %vecinit6.i
}

; FIXME: Pointer adjusted broadcasts

define <4 x i32> @load_splat_4i32_4i32_1111(<4 x i32>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_4i32_4i32_1111:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vpshufd {{.*#+}} xmm0 = mem[1,1,1,1]
; CHECK-NEXT:    retq
entry:
  %ld = load <4 x i32>, <4 x i32>* %ptr
  %ret = shufflevector <4 x i32> %ld, <4 x i32> undef, <4 x i32> <i32 1, i32 1, i32 1, i32 1>
  ret <4 x i32> %ret
}

define <8 x i32> @load_splat_8i32_4i32_33333333(<4 x i32>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_8i32_4i32_33333333:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vpermilps {{.*#+}} xmm0 = mem[3,3,3,3]
; CHECK-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <4 x i32>, <4 x i32>* %ptr
  %ret = shufflevector <4 x i32> %ld, <4 x i32> undef, <8 x i32> <i32 3, i32 3, i32 3, i32 3, i32 3, i32 3, i32 3, i32 3>
  ret <8 x i32> %ret
}

define <8 x i32> @load_splat_8i32_8i32_55555555(<8 x i32>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_8i32_8i32_55555555:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovaps (%rdi), %ymm0
; CHECK-NEXT:    vextractf128 $1, %ymm0, %xmm0
; CHECK-NEXT:    vpermilps {{.*#+}} xmm0 = xmm0[1,1,1,1]
; CHECK-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <8 x i32>, <8 x i32>* %ptr
  %ret = shufflevector <8 x i32> %ld, <8 x i32> undef, <8 x i32> <i32 5, i32 5, i32 5, i32 5, i32 5, i32 5, i32 5, i32 5>
  ret <8 x i32> %ret
}

define <4 x float> @load_splat_4f32_4f32_1111(<4 x float>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_4f32_4f32_1111:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss 4(%rdi), %xmm0
; CHECK-NEXT:    retq
entry:
  %ld = load <4 x float>, <4 x float>* %ptr
  %ret = shufflevector <4 x float> %ld, <4 x float> undef, <4 x i32> <i32 1, i32 1, i32 1, i32 1>
  ret <4 x float> %ret
}

define <8 x float> @load_splat_8f32_4f32_33333333(<4 x float>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_8f32_4f32_33333333:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss 12(%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <4 x float>, <4 x float>* %ptr
  %ret = shufflevector <4 x float> %ld, <4 x float> undef, <8 x i32> <i32 3, i32 3, i32 3, i32 3, i32 3, i32 3, i32 3, i32 3>
  ret <8 x float> %ret
}

define <8 x float> @load_splat_8f32_8f32_55555555(<8 x float>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_8f32_8f32_55555555:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss 20(%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <8 x float>, <8 x float>* %ptr
  %ret = shufflevector <8 x float> %ld, <8 x float> undef, <8 x i32> <i32 5, i32 5, i32 5, i32 5, i32 5, i32 5, i32 5, i32 5>
  ret <8 x float> %ret
}

define <2 x i64> @load_splat_2i64_2i64_1111(<2 x i64>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_2i64_2i64_1111:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vpshufd {{.*#+}} xmm0 = mem[2,3,2,3]
; CHECK-NEXT:    retq
entry:
  %ld = load <2 x i64>, <2 x i64>* %ptr
  %ret = shufflevector <2 x i64> %ld, <2 x i64> undef, <2 x i32> <i32 1, i32 1>
  ret <2 x i64> %ret
}

define <4 x i64> @load_splat_4i64_2i64_1111(<2 x i64>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_4i64_2i64_1111:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovaps (%rdi), %xmm0
; CHECK-NEXT:    vmovhlps {{.*#+}} xmm0 = xmm0[1,1]
; CHECK-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <2 x i64>, <2 x i64>* %ptr
  %ret = shufflevector <2 x i64> %ld, <2 x i64> undef, <4 x i32> <i32 1, i32 1, i32 1, i32 1>
  ret <4 x i64> %ret
}

define <4 x i64> @load_splat_4i64_4i64_2222(<4 x i64>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_4i64_4i64_2222:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovapd (%rdi), %ymm0
; CHECK-NEXT:    vextractf128 $1, %ymm0, %xmm0
; CHECK-NEXT:    vmovddup {{.*#+}} xmm0 = xmm0[0,0]
; CHECK-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <4 x i64>, <4 x i64>* %ptr
  %ret = shufflevector <4 x i64> %ld, <4 x i64> undef, <4 x i32> <i32 2, i32 2, i32 2, i32 2>
  ret <4 x i64> %ret
}

define <2 x double> @load_splat_2f64_2f64_1111(<2 x double>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_2f64_2f64_1111:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovaps (%rdi), %xmm0
; CHECK-NEXT:    vmovhlps {{.*#+}} xmm0 = xmm0[1,1]
; CHECK-NEXT:    retq
entry:
  %ld = load <2 x double>, <2 x double>* %ptr
  %ret = shufflevector <2 x double> %ld, <2 x double> undef, <2 x i32> <i32 1, i32 1>
  ret <2 x double> %ret
}

define <4 x double> @load_splat_4f64_2f64_1111(<2 x double>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_4f64_2f64_1111:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastsd 8(%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <2 x double>, <2 x double>* %ptr
  %ret = shufflevector <2 x double> %ld, <2 x double> undef, <4 x i32> <i32 1, i32 1, i32 1, i32 1>
  ret <4 x double> %ret
}

define <4 x double> @load_splat_4f64_4f64_2222(<4 x double>* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: load_splat_4f64_4f64_2222:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastsd 16(%rdi), %ymm0
; CHECK-NEXT:    retq
entry:
  %ld = load <4 x double>, <4 x double>* %ptr
  %ret = shufflevector <4 x double> %ld, <4 x double> undef, <4 x i32> <i32 2, i32 2, i32 2, i32 2>
  ret <4 x double> %ret
}

; Unsupported vbroadcasts

define <2 x i64> @G(i64* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: G:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovq {{.*#+}} xmm0 = mem[0],zero
; CHECK-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,1,0,1]
; CHECK-NEXT:    retq
entry:
  %q = load i64, i64* %ptr, align 8
  %vecinit.i = insertelement <2 x i64> undef, i64 %q, i32 0
  %vecinit2.i = insertelement <2 x i64> %vecinit.i, i64 %q, i32 1
  ret <2 x i64> %vecinit2.i
}

define <4 x i32> @H(<4 x i32> %a) {
; CHECK-LABEL: H:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[1,1,2,3]
; CHECK-NEXT:    retq
entry:
  %x = shufflevector <4 x i32> %a, <4 x i32> undef, <4 x i32> <i32 1, i32 undef, i32 undef, i32 undef>
  ret <4 x i32> %x
}

define <2 x double> @I(double* %ptr) nounwind uwtable readnone ssp {
; CHECK-LABEL: I:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vmovddup {{.*#+}} xmm0 = mem[0,0]
; CHECK-NEXT:    retq
entry:
  %q = load double, double* %ptr, align 4
  %vecinit.i = insertelement <2 x double> undef, double %q, i32 0
  %vecinit2.i = insertelement <2 x double> %vecinit.i, double %q, i32 1
  ret <2 x double> %vecinit2.i
}

define <4 x float> @_RR(float* %ptr, i32* %k) nounwind uwtable readnone ssp {
; CHECK-LABEL: _RR:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss (%rdi), %xmm0
; CHECK-NEXT:    movl (%rsi), %eax
; CHECK-NEXT:    movl %eax, (%rax)
; CHECK-NEXT:    retq
entry:
  %q = load float, float* %ptr, align 4
  %vecinit.i = insertelement <4 x float> undef, float %q, i32 0
  %vecinit2.i = insertelement <4 x float> %vecinit.i, float %q, i32 1
  %vecinit4.i = insertelement <4 x float> %vecinit2.i, float %q, i32 2
  %vecinit6.i = insertelement <4 x float> %vecinit4.i, float %q, i32 3
  ; force a chain
  %j = load i32, i32* %k, align 4
  store i32 %j, i32* undef
  ret <4 x float> %vecinit6.i
}

define <4 x float> @_RR2(float* %ptr, i32* %k) nounwind uwtable readnone ssp {
; CHECK-LABEL: _RR2:
; CHECK:       ## BB#0: ## %entry
; CHECK-NEXT:    vbroadcastss (%rdi), %xmm0
; CHECK-NEXT:    retq
entry:
  %q = load float, float* %ptr, align 4
  %v = insertelement <4 x float> undef, float %q, i32 0
  %t = shufflevector <4 x float> %v, <4 x float> undef, <4 x i32> zeroinitializer
  ret <4 x float> %t
}

; These tests check that a vbroadcast instruction is used when we have a splat
; formed from a concat_vectors (via the shufflevector) of two BUILD_VECTORs
; (via the insertelements).

define <8 x float> @splat_concat1(float* %p) {
; CHECK-LABEL: splat_concat1:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vbroadcastss (%rdi), %ymm0
; CHECK-NEXT:    retq
  %1 = load float, float* %p, align 4
  %2 = insertelement <4 x float> undef, float %1, i32 0
  %3 = insertelement <4 x float> %2, float %1, i32 1
  %4 = insertelement <4 x float> %3, float %1, i32 2
  %5 = insertelement <4 x float> %4, float %1, i32 3
  %6 = shufflevector <4 x float> %5, <4 x float> undef, <8 x i32> <i32 0, i32 1, i32 2, i32 3, i32 0, i32 1, i32 2, i32 3>
  ret <8 x float> %6
}

define <8 x float> @splat_concat2(float* %p) {
; CHECK-LABEL: splat_concat2:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vbroadcastss (%rdi), %ymm0
; CHECK-NEXT:    retq
  %1 = load float, float* %p, align 4
  %2 = insertelement <4 x float> undef, float %1, i32 0
  %3 = insertelement <4 x float> %2, float %1, i32 1
  %4 = insertelement <4 x float> %3, float %1, i32 2
  %5 = insertelement <4 x float> %4, float %1, i32 3
  %6 = insertelement <4 x float> undef, float %1, i32 0
  %7 = insertelement <4 x float> %6, float %1, i32 1
  %8 = insertelement <4 x float> %7, float %1, i32 2
  %9 = insertelement <4 x float> %8, float %1, i32 3
  %10 = shufflevector <4 x float> %5, <4 x float> %9, <8 x i32> <i32 0, i32 1, i32 2, i32 3, i32 4, i32 5, i32 6, i32 7>
  ret <8 x float> %10
}

define <4 x double> @splat_concat3(double* %p) {
; CHECK-LABEL: splat_concat3:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vbroadcastsd (%rdi), %ymm0
; CHECK-NEXT:    retq
  %1 = load double, double* %p, align 8
  %2 = insertelement <2 x double> undef, double %1, i32 0
  %3 = insertelement <2 x double> %2, double %1, i32 1
  %4 = shufflevector <2 x double> %3, <2 x double> undef, <4 x i32> <i32 0, i32 1, i32 0, i32 1>
  ret <4 x double> %4
}

define <4 x double> @splat_concat4(double* %p) {
; CHECK-LABEL: splat_concat4:
; CHECK:       ## BB#0:
; CHECK-NEXT:    vbroadcastsd (%rdi), %ymm0
; CHECK-NEXT:    retq
  %1 = load double, double* %p, align 8
  %2 = insertelement <2 x double> undef, double %1, i32 0
  %3 = insertelement <2 x double> %2, double %1, i32 1
  %4 = insertelement <2 x double> undef, double %1, i32 0
  %5 = insertelement <2 x double> %2, double %1, i32 1
  %6 = shufflevector <2 x double> %3, <2 x double> %5, <4 x i32> <i32 0, i32 1, i32 2, i32 3>
  ret <4 x double> %6
}
