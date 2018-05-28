package ru.reeson2003.asm;

public class AsmFunctions {
    public AsmFunctions(String libPath) {
        System.loadLibrary(libPath);
    }

    public native int asm_string_length(String text);

    public native int asm_index_of(String text, String substring);

    public native String asm_substring(String text, int begin, int length);
}