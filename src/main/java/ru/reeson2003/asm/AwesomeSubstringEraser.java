package ru.reeson2003.asm;

/**
 * Date: 27.05.2018.
 * Time: 20:24.
 *
 * @author Pavel Gavrilov.
 */
public class AwesomeSubstringEraser implements SubstringEraser {
    @Override
    public String eraseAll(String baseString, String substring) {
        AsmFunctions asm = new AsmFunctions();
        String toSearch = baseString;
        int substringLength = asm.asm_string_length(substring);
        StringBuilder stringBuilder = new StringBuilder();
        while (true) {
            int i = asm.asm_index_of(toSearch, substring);
            if (i < 0) {
                stringBuilder.append(toSearch);
                break;
            }
            int toSearchLength = asm.asm_string_length(toSearch);
            String head = asm.asm_substring(toSearch, 0, i);
            stringBuilder.append(head);
            toSearch = asm.asm_substring(toSearch, i + substringLength, toSearchLength - i - substringLength);
        }
        return stringBuilder.toString();
    }
}
