#ifndef __IDT_H_
#define __IDT_H_

#include <stdint.h>

typedef struct {
	uint16_t offset_0_15;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_16_31;
} __attribute__((packed)) idt_descriptor;

struct cpu_state {
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	
	uint32_t vector;
	
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
};

#define IDT_32BIT_INTERRUPT_GATE	0xE
#define IDT_STORAGE_SEGMENT			0x20
#define IDT_DPL_3					0x60
#define IDT_PRESENT					0x80

#define INT_START asm volatile("pusha");
#define INT_END asm volatile("popa"); asm volatile("iret");

extern void _set_idtr();

void initalize_idt();
extern void generic_interrupt_wrapper();
	
extern void idt_init();
extern void exceptions_init();
extern void idt_register_interrupt(uint8_t i, uint32_t addr);
extern void add_idt_descriptor(uint8_t id, idt_descriptor desc);


extern void interrupt_wrapper_0();
extern void interrupt_wrapper_1();
extern void interrupt_wrapper_2();
extern void interrupt_wrapper_3();
extern void interrupt_wrapper_4();
extern void interrupt_wrapper_5();
extern void interrupt_wrapper_6();
extern void interrupt_wrapper_7();
extern void interrupt_wrapper_8();
extern void interrupt_wrapper_9();
extern void interrupt_wrapper_10();
extern void interrupt_wrapper_11();
extern void interrupt_wrapper_12();
extern void interrupt_wrapper_13();
extern void interrupt_wrapper_14();
extern void interrupt_wrapper_15();
extern void interrupt_wrapper_16();
extern void interrupt_wrapper_17();
extern void interrupt_wrapper_18();
extern void interrupt_wrapper_19();
extern void interrupt_wrapper_20();
extern void interrupt_wrapper_21();
extern void interrupt_wrapper_22();
extern void interrupt_wrapper_23();
extern void interrupt_wrapper_24();
extern void interrupt_wrapper_25();
extern void interrupt_wrapper_26();
extern void interrupt_wrapper_27();
extern void interrupt_wrapper_28();
extern void interrupt_wrapper_29();
extern void interrupt_wrapper_30();
extern void interrupt_wrapper_31();
extern void interrupt_wrapper_32();
extern void interrupt_wrapper_33();
extern void interrupt_wrapper_34();
extern void interrupt_wrapper_35();
extern void interrupt_wrapper_36();
extern void interrupt_wrapper_37();
extern void interrupt_wrapper_38();
extern void interrupt_wrapper_39();
extern void interrupt_wrapper_40();
extern void interrupt_wrapper_41();
extern void interrupt_wrapper_42();
extern void interrupt_wrapper_43();
extern void interrupt_wrapper_44();
extern void interrupt_wrapper_45();
extern void interrupt_wrapper_46();
extern void interrupt_wrapper_47();
extern void interrupt_wrapper_48();
extern void interrupt_wrapper_49();
extern void interrupt_wrapper_50();
extern void interrupt_wrapper_51();
extern void interrupt_wrapper_52();
extern void interrupt_wrapper_53();
extern void interrupt_wrapper_54();
extern void interrupt_wrapper_55();
extern void interrupt_wrapper_56();
extern void interrupt_wrapper_57();
extern void interrupt_wrapper_58();
extern void interrupt_wrapper_59();
extern void interrupt_wrapper_60();
extern void interrupt_wrapper_61();
extern void interrupt_wrapper_62();
extern void interrupt_wrapper_63();
extern void interrupt_wrapper_64();
extern void interrupt_wrapper_65();
extern void interrupt_wrapper_66();
extern void interrupt_wrapper_67();
extern void interrupt_wrapper_68();
extern void interrupt_wrapper_69();
extern void interrupt_wrapper_70();
extern void interrupt_wrapper_71();
extern void interrupt_wrapper_72();
extern void interrupt_wrapper_73();
extern void interrupt_wrapper_74();
extern void interrupt_wrapper_75();
extern void interrupt_wrapper_76();
extern void interrupt_wrapper_77();
extern void interrupt_wrapper_78();
extern void interrupt_wrapper_79();
extern void interrupt_wrapper_80();
extern void interrupt_wrapper_81();
extern void interrupt_wrapper_82();
extern void interrupt_wrapper_83();
extern void interrupt_wrapper_84();
extern void interrupt_wrapper_85();
extern void interrupt_wrapper_86();
extern void interrupt_wrapper_87();
extern void interrupt_wrapper_88();
extern void interrupt_wrapper_89();
extern void interrupt_wrapper_90();
extern void interrupt_wrapper_91();
extern void interrupt_wrapper_92();
extern void interrupt_wrapper_93();
extern void interrupt_wrapper_94();
extern void interrupt_wrapper_95();
extern void interrupt_wrapper_96();
extern void interrupt_wrapper_97();
extern void interrupt_wrapper_98();
extern void interrupt_wrapper_99();
extern void interrupt_wrapper_100();
extern void interrupt_wrapper_101();
extern void interrupt_wrapper_102();
extern void interrupt_wrapper_103();
extern void interrupt_wrapper_104();
extern void interrupt_wrapper_105();
extern void interrupt_wrapper_106();
extern void interrupt_wrapper_107();
extern void interrupt_wrapper_108();
extern void interrupt_wrapper_109();
extern void interrupt_wrapper_110();
extern void interrupt_wrapper_111();
extern void interrupt_wrapper_112();
extern void interrupt_wrapper_113();
extern void interrupt_wrapper_114();
extern void interrupt_wrapper_115();
extern void interrupt_wrapper_116();
extern void interrupt_wrapper_117();
extern void interrupt_wrapper_118();
extern void interrupt_wrapper_119();
extern void interrupt_wrapper_120();
extern void interrupt_wrapper_121();
extern void interrupt_wrapper_122();
extern void interrupt_wrapper_123();
extern void interrupt_wrapper_124();
extern void interrupt_wrapper_125();
extern void interrupt_wrapper_126();
extern void interrupt_wrapper_127();
extern void interrupt_wrapper_128();
extern void interrupt_wrapper_129();
extern void interrupt_wrapper_130();
extern void interrupt_wrapper_131();
extern void interrupt_wrapper_132();
extern void interrupt_wrapper_133();
extern void interrupt_wrapper_134();
extern void interrupt_wrapper_135();
extern void interrupt_wrapper_136();
extern void interrupt_wrapper_137();
extern void interrupt_wrapper_138();
extern void interrupt_wrapper_139();
extern void interrupt_wrapper_140();
extern void interrupt_wrapper_141();
extern void interrupt_wrapper_142();
extern void interrupt_wrapper_143();
extern void interrupt_wrapper_144();
extern void interrupt_wrapper_145();
extern void interrupt_wrapper_146();
extern void interrupt_wrapper_147();
extern void interrupt_wrapper_148();
extern void interrupt_wrapper_149();
extern void interrupt_wrapper_150();
extern void interrupt_wrapper_151();
extern void interrupt_wrapper_152();
extern void interrupt_wrapper_153();
extern void interrupt_wrapper_154();
extern void interrupt_wrapper_155();
extern void interrupt_wrapper_156();
extern void interrupt_wrapper_157();
extern void interrupt_wrapper_158();
extern void interrupt_wrapper_159();
extern void interrupt_wrapper_160();
extern void interrupt_wrapper_161();
extern void interrupt_wrapper_162();
extern void interrupt_wrapper_163();
extern void interrupt_wrapper_164();
extern void interrupt_wrapper_165();
extern void interrupt_wrapper_166();
extern void interrupt_wrapper_167();
extern void interrupt_wrapper_168();
extern void interrupt_wrapper_169();
extern void interrupt_wrapper_170();
extern void interrupt_wrapper_171();
extern void interrupt_wrapper_172();
extern void interrupt_wrapper_173();
extern void interrupt_wrapper_174();
extern void interrupt_wrapper_175();
extern void interrupt_wrapper_176();
extern void interrupt_wrapper_177();
extern void interrupt_wrapper_178();
extern void interrupt_wrapper_179();
extern void interrupt_wrapper_180();
extern void interrupt_wrapper_181();
extern void interrupt_wrapper_182();
extern void interrupt_wrapper_183();
extern void interrupt_wrapper_184();
extern void interrupt_wrapper_185();
extern void interrupt_wrapper_186();
extern void interrupt_wrapper_187();
extern void interrupt_wrapper_188();
extern void interrupt_wrapper_189();
extern void interrupt_wrapper_190();
extern void interrupt_wrapper_191();
extern void interrupt_wrapper_192();
extern void interrupt_wrapper_193();
extern void interrupt_wrapper_194();
extern void interrupt_wrapper_195();
extern void interrupt_wrapper_196();
extern void interrupt_wrapper_197();
extern void interrupt_wrapper_198();
extern void interrupt_wrapper_199();
extern void interrupt_wrapper_200();
extern void interrupt_wrapper_201();
extern void interrupt_wrapper_202();
extern void interrupt_wrapper_203();
extern void interrupt_wrapper_204();
extern void interrupt_wrapper_205();
extern void interrupt_wrapper_206();
extern void interrupt_wrapper_207();
extern void interrupt_wrapper_208();
extern void interrupt_wrapper_209();
extern void interrupt_wrapper_210();
extern void interrupt_wrapper_211();
extern void interrupt_wrapper_212();
extern void interrupt_wrapper_213();
extern void interrupt_wrapper_214();
extern void interrupt_wrapper_215();
extern void interrupt_wrapper_216();
extern void interrupt_wrapper_217();
extern void interrupt_wrapper_218();
extern void interrupt_wrapper_219();
extern void interrupt_wrapper_220();
extern void interrupt_wrapper_221();
extern void interrupt_wrapper_222();
extern void interrupt_wrapper_223();
extern void interrupt_wrapper_224();
extern void interrupt_wrapper_225();
extern void interrupt_wrapper_226();
extern void interrupt_wrapper_227();
extern void interrupt_wrapper_228();
extern void interrupt_wrapper_229();
extern void interrupt_wrapper_230();
extern void interrupt_wrapper_231();
extern void interrupt_wrapper_232();
extern void interrupt_wrapper_233();
extern void interrupt_wrapper_234();
extern void interrupt_wrapper_235();
extern void interrupt_wrapper_236();
extern void interrupt_wrapper_237();
extern void interrupt_wrapper_238();
extern void interrupt_wrapper_239();
extern void interrupt_wrapper_240();
extern void interrupt_wrapper_241();
extern void interrupt_wrapper_242();
extern void interrupt_wrapper_243();
extern void interrupt_wrapper_244();
extern void interrupt_wrapper_245();
extern void interrupt_wrapper_246();
extern void interrupt_wrapper_247();
extern void interrupt_wrapper_248();
extern void interrupt_wrapper_249();
extern void interrupt_wrapper_250();
extern void interrupt_wrapper_251();
extern void interrupt_wrapper_252();
extern void interrupt_wrapper_253();
extern void interrupt_wrapper_254();
extern void interrupt_wrapper_255();


#endif
