/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_1012(char*, char *);
extern void execute_1013(char*, char *);
extern void execute_1014(char*, char *);
extern void execute_1019(char*, char *);
extern void execute_1020(char*, char *);
extern void execute_1021(char*, char *);
extern void execute_1011(char*, char *);
extern void execute_128(char*, char *);
extern void execute_206(char*, char *);
extern void execute_979(char*, char *);
extern void execute_980(char*, char *);
extern void execute_988(char*, char *);
extern void execute_996(char*, char *);
extern void execute_997(char*, char *);
extern void execute_211(char*, char *);
extern void execute_213(char*, char *);
extern void execute_238(char*, char *);
extern void execute_216(char*, char *);
extern void execute_217(char*, char *);
extern void execute_241(char*, char *);
extern void execute_245(char*, char *);
extern void execute_255(char*, char *);
extern void execute_251(char*, char *);
extern void execute_252(char*, char *);
extern void execute_259(char*, char *);
extern void execute_986(char*, char *);
extern void execute_983(char*, char *);
extern void execute_984(char*, char *);
extern void execute_992(char*, char *);
extern void execute_993(char*, char *);
extern void execute_994(char*, char *);
extern void execute_146(char*, char *);
extern void execute_147(char*, char *);
extern void execute_167(char*, char *);
extern void execute_137(char*, char *);
extern void execute_143(char*, char *);
extern void execute_144(char*, char *);
extern void execute_141(char*, char *);
extern void execute_149(char*, char *);
extern void execute_151(char*, char *);
extern void execute_153(char*, char *);
extern void execute_155(char*, char *);
extern void execute_157(char*, char *);
extern void execute_159(char*, char *);
extern void execute_161(char*, char *);
extern void execute_163(char*, char *);
extern void execute_165(char*, char *);
extern void execute_234(char*, char *);
extern void execute_235(char*, char *);
extern void execute_237(char*, char *);
extern void execute_226(char*, char *);
extern void execute_231(char*, char *);
extern void execute_232(char*, char *);
extern void execute_229(char*, char *);
extern void execute_265(char*, char *);
extern void execute_972(char*, char *);
extern void execute_973(char*, char *);
extern void execute_269(char*, char *);
extern void execute_271(char*, char *);
extern void execute_311(char*, char *);
extern void execute_313(char*, char *);
extern void execute_314(char*, char *);
extern void execute_620(char*, char *);
extern void execute_942(char*, char *);
extern void execute_943(char*, char *);
extern void execute_958(char*, char *);
extern void execute_920(char*, char *);
extern void execute_946(char*, char *);
extern void execute_947(char*, char *);
extern void execute_277(char*, char *);
extern void execute_278(char*, char *);
extern void execute_279(char*, char *);
extern void execute_285(char*, char *);
extern void execute_303(char*, char *);
extern void execute_304(char*, char *);
extern void execute_306(char*, char *);
extern void execute_294(char*, char *);
extern void execute_300(char*, char *);
extern void execute_301(char*, char *);
extern void execute_298(char*, char *);
extern void execute_332(char*, char *);
extern void execute_379(char*, char *);
extern void execute_542(char*, char *);
extern void execute_543(char*, char *);
extern void execute_544(char*, char *);
extern void execute_565(char*, char *);
extern void execute_329(char*, char *);
extern void execute_330(char*, char *);
extern void execute_401(char*, char *);
extern void execute_462(char*, char *);
extern void execute_463(char*, char *);
extern void execute_464(char*, char *);
extern void execute_465(char*, char *);
extern void execute_466(char*, char *);
extern void execute_467(char*, char *);
extern void execute_470(char*, char *);
extern void execute_472(char*, char *);
extern void execute_476(char*, char *);
extern void execute_477(char*, char *);
extern void execute_518(char*, char *);
extern void execute_519(char*, char *);
extern void execute_520(char*, char *);
extern void execute_567(char*, char *);
extern void execute_568(char*, char *);
extern void execute_569(char*, char *);
extern void execute_570(char*, char *);
extern void execute_571(char*, char *);
extern void execute_572(char*, char *);
extern void execute_573(char*, char *);
extern void execute_594(char*, char *);
extern void execute_595(char*, char *);
extern void execute_375(char*, char *);
extern void execute_376(char*, char *);
extern void execute_378(char*, char *);
extern void execute_366(char*, char *);
extern void execute_372(char*, char *);
extern void execute_373(char*, char *);
extern void execute_370(char*, char *);
extern void execute_438(char*, char *);
extern void execute_439(char*, char *);
extern void execute_441(char*, char *);
extern void execute_429(char*, char *);
extern void execute_435(char*, char *);
extern void execute_436(char*, char *);
extern void execute_433(char*, char *);
extern void execute_537(char*, char *);
extern void execute_538(char*, char *);
extern void execute_540(char*, char *);
extern void execute_528(char*, char *);
extern void execute_534(char*, char *);
extern void execute_535(char*, char *);
extern void execute_532(char*, char *);
extern void execute_590(char*, char *);
extern void execute_591(char*, char *);
extern void execute_593(char*, char *);
extern void execute_581(char*, char *);
extern void execute_587(char*, char *);
extern void execute_588(char*, char *);
extern void execute_585(char*, char *);
extern void execute_951(char*, char *);
extern void execute_630(char*, char *);
extern void execute_633(char*, char *);
extern void execute_691(char*, char *);
extern void execute_692(char*, char *);
extern void execute_639(char*, char *);
extern void execute_640(char*, char *);
extern void execute_645(char*, char *);
extern void execute_646(char*, char *);
extern void execute_647(char*, char *);
extern void execute_648(char*, char *);
extern void execute_649(char*, char *);
extern void execute_652(char*, char *);
extern void execute_657(char*, char *);
extern void execute_658(char*, char *);
extern void execute_659(char*, char *);
extern void execute_660(char*, char *);
extern void execute_661(char*, char *);
extern void execute_664(char*, char *);
extern void execute_696(char*, char *);
extern void execute_697(char*, char *);
extern void execute_701(char*, char *);
extern void execute_743(char*, char *);
extern void execute_744(char*, char *);
extern void execute_747(char*, char *);
extern void execute_748(char*, char *);
extern void execute_749(char*, char *);
extern void execute_750(char*, char *);
extern void execute_751(char*, char *);
extern void execute_752(char*, char *);
extern void execute_753(char*, char *);
extern void execute_754(char*, char *);
extern void execute_835(char*, char *);
extern void execute_836(char*, char *);
extern void execute_837(char*, char *);
extern void execute_838(char*, char *);
extern void execute_681(char*, char *);
extern void execute_682(char*, char *);
extern void execute_690(char*, char *);
extern void execute_672(char*, char *);
extern void execute_678(char*, char *);
extern void execute_679(char*, char *);
extern void execute_676(char*, char *);
extern void execute_684(char*, char *);
extern void execute_686(char*, char *);
extern void execute_688(char*, char *);
extern void execute_718(char*, char *);
extern void execute_719(char*, char *);
extern void execute_721(char*, char *);
extern void execute_709(char*, char *);
extern void execute_715(char*, char *);
extern void execute_716(char*, char *);
extern void execute_713(char*, char *);
extern void execute_771(char*, char *);
extern void execute_772(char*, char *);
extern void execute_774(char*, char *);
extern void execute_762(char*, char *);
extern void execute_768(char*, char *);
extern void execute_769(char*, char *);
extern void execute_766(char*, char *);
extern void execute_791(char*, char *);
extern void execute_792(char*, char *);
extern void execute_794(char*, char *);
extern void execute_782(char*, char *);
extern void execute_788(char*, char *);
extern void execute_789(char*, char *);
extern void execute_786(char*, char *);
extern void execute_964(char*, char *);
extern void execute_1016(char*, char *);
extern void execute_1017(char*, char *);
extern void execute_1018(char*, char *);
extern void execute_1022(char*, char *);
extern void execute_1023(char*, char *);
extern void execute_1024(char*, char *);
extern void execute_1025(char*, char *);
extern void execute_1026(char*, char *);
extern void transaction_3(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_4(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_5(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_7(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_8(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_10(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_11(char*, char*, unsigned, unsigned, unsigned);
extern void vhdl_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_35(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_53(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_54(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_57(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_58(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_64(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_65(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_68(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_69(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_70(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_77(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_91(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_95(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_102(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_111(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_233(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_234(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_235(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_237(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_252(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_253(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_282(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_283(char*, char*, unsigned, unsigned, unsigned);
extern void vlog_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_9(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[248] = {(funcp)execute_1012, (funcp)execute_1013, (funcp)execute_1014, (funcp)execute_1019, (funcp)execute_1020, (funcp)execute_1021, (funcp)execute_1011, (funcp)execute_128, (funcp)execute_206, (funcp)execute_979, (funcp)execute_980, (funcp)execute_988, (funcp)execute_996, (funcp)execute_997, (funcp)execute_211, (funcp)execute_213, (funcp)execute_238, (funcp)execute_216, (funcp)execute_217, (funcp)execute_241, (funcp)execute_245, (funcp)execute_255, (funcp)execute_251, (funcp)execute_252, (funcp)execute_259, (funcp)execute_986, (funcp)execute_983, (funcp)execute_984, (funcp)execute_992, (funcp)execute_993, (funcp)execute_994, (funcp)execute_146, (funcp)execute_147, (funcp)execute_167, (funcp)execute_137, (funcp)execute_143, (funcp)execute_144, (funcp)execute_141, (funcp)execute_149, (funcp)execute_151, (funcp)execute_153, (funcp)execute_155, (funcp)execute_157, (funcp)execute_159, (funcp)execute_161, (funcp)execute_163, (funcp)execute_165, (funcp)execute_234, (funcp)execute_235, (funcp)execute_237, (funcp)execute_226, (funcp)execute_231, (funcp)execute_232, (funcp)execute_229, (funcp)execute_265, (funcp)execute_972, (funcp)execute_973, (funcp)execute_269, (funcp)execute_271, (funcp)execute_311, (funcp)execute_313, (funcp)execute_314, (funcp)execute_620, (funcp)execute_942, (funcp)execute_943, (funcp)execute_958, (funcp)execute_920, (funcp)execute_946, (funcp)execute_947, (funcp)execute_277, (funcp)execute_278, (funcp)execute_279, (funcp)execute_285, (funcp)execute_303, (funcp)execute_304, (funcp)execute_306, (funcp)execute_294, (funcp)execute_300, (funcp)execute_301, (funcp)execute_298, (funcp)execute_332, (funcp)execute_379, (funcp)execute_542, (funcp)execute_543, (funcp)execute_544, (funcp)execute_565, (funcp)execute_329, (funcp)execute_330, (funcp)execute_401, (funcp)execute_462, (funcp)execute_463, (funcp)execute_464, (funcp)execute_465, (funcp)execute_466, (funcp)execute_467, (funcp)execute_470, (funcp)execute_472, (funcp)execute_476, (funcp)execute_477, (funcp)execute_518, (funcp)execute_519, (funcp)execute_520, (funcp)execute_567, (funcp)execute_568, (funcp)execute_569, (funcp)execute_570, (funcp)execute_571, (funcp)execute_572, (funcp)execute_573, (funcp)execute_594, (funcp)execute_595, (funcp)execute_375, (funcp)execute_376, (funcp)execute_378, (funcp)execute_366, (funcp)execute_372, (funcp)execute_373, (funcp)execute_370, (funcp)execute_438, (funcp)execute_439, (funcp)execute_441, (funcp)execute_429, (funcp)execute_435, (funcp)execute_436, (funcp)execute_433, (funcp)execute_537, (funcp)execute_538, (funcp)execute_540, (funcp)execute_528, (funcp)execute_534, (funcp)execute_535, (funcp)execute_532, (funcp)execute_590, (funcp)execute_591, (funcp)execute_593, (funcp)execute_581, (funcp)execute_587, (funcp)execute_588, (funcp)execute_585, (funcp)execute_951, (funcp)execute_630, (funcp)execute_633, (funcp)execute_691, (funcp)execute_692, (funcp)execute_639, (funcp)execute_640, (funcp)execute_645, (funcp)execute_646, (funcp)execute_647, (funcp)execute_648, (funcp)execute_649, (funcp)execute_652, (funcp)execute_657, (funcp)execute_658, (funcp)execute_659, (funcp)execute_660, (funcp)execute_661, (funcp)execute_664, (funcp)execute_696, (funcp)execute_697, (funcp)execute_701, (funcp)execute_743, (funcp)execute_744, (funcp)execute_747, (funcp)execute_748, (funcp)execute_749, (funcp)execute_750, (funcp)execute_751, (funcp)execute_752, (funcp)execute_753, (funcp)execute_754, (funcp)execute_835, (funcp)execute_836, (funcp)execute_837, (funcp)execute_838, (funcp)execute_681, (funcp)execute_682, (funcp)execute_690, (funcp)execute_672, (funcp)execute_678, (funcp)execute_679, (funcp)execute_676, (funcp)execute_684, (funcp)execute_686, (funcp)execute_688, (funcp)execute_718, (funcp)execute_719, (funcp)execute_721, (funcp)execute_709, (funcp)execute_715, (funcp)execute_716, (funcp)execute_713, (funcp)execute_771, (funcp)execute_772, (funcp)execute_774, (funcp)execute_762, (funcp)execute_768, (funcp)execute_769, (funcp)execute_766, (funcp)execute_791, (funcp)execute_792, (funcp)execute_794, (funcp)execute_782, (funcp)execute_788, (funcp)execute_789, (funcp)execute_786, (funcp)execute_964, (funcp)execute_1016, (funcp)execute_1017, (funcp)execute_1018, (funcp)execute_1022, (funcp)execute_1023, (funcp)execute_1024, (funcp)execute_1025, (funcp)execute_1026, (funcp)transaction_3, (funcp)transaction_4, (funcp)transaction_5, (funcp)transaction_7, (funcp)transaction_8, (funcp)transaction_10, (funcp)transaction_11, (funcp)vhdl_transfunc_eventcallback, (funcp)transaction_35, (funcp)transaction_53, (funcp)transaction_54, (funcp)transaction_57, (funcp)transaction_58, (funcp)transaction_64, (funcp)transaction_65, (funcp)transaction_68, (funcp)transaction_69, (funcp)transaction_70, (funcp)transaction_77, (funcp)transaction_91, (funcp)transaction_95, (funcp)transaction_102, (funcp)transaction_111, (funcp)transaction_233, (funcp)transaction_234, (funcp)transaction_235, (funcp)transaction_237, (funcp)transaction_252, (funcp)transaction_253, (funcp)transaction_282, (funcp)transaction_283, (funcp)vlog_transfunc_eventcallback, (funcp)transaction_9};
const int NumRelocateId= 248;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/phase_creater_bd_behav/xsim.reloc",  (void **)funcTab, 248);
	iki_vhdl_file_variable_register(dp + 252184);
	iki_vhdl_file_variable_register(dp + 252240);


	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/phase_creater_bd_behav/xsim.reloc");
}

	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net

void wrapper_func_0(char *dp)

{

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 522856, dp + 520440, 0, 15, 16, 31, 16, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 522896, dp + 522168, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 522952, dp + 522168, 1, 1, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 522800, dp + 522224, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 522856, dp + 522336, 0, 15, 0, 15, 16, 1);

}

void simulate(char *dp)
{
		iki_schedule_processes_at_time_zero(dp, "xsim.dir/phase_creater_bd_behav/xsim.reloc");
	wrapper_func_0(dp);

	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

extern SYSTEMCLIB_IMP_DLLSPEC void local_register_implicit_channel(int, char*);
extern void implicit_HDL_SCinstatiate();

extern SYSTEMCLIB_IMP_DLLSPEC int xsim_argc_copy ;
extern SYSTEMCLIB_IMP_DLLSPEC char** xsim_argv_copy ;

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/phase_creater_bd_behav/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/phase_creater_bd_behav/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/phase_creater_bd_behav/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
