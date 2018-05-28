package ru.reeson2003.asm;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Date: 27.05.2018.
 * Time: 18:51.
 *
 * @author Pavel Gavrilov.
 */
public class Program implements Title{

    public static final String DLL_RELATIVE_PATH = "/lib/awssembler.dll";
    public static final String USER_DIR = "user.dir";

    public static void main(String[] args) {
        try {
            printTitle();
            String dllPath = getDllPath();
            BufferedReader isReader = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Введите путь к исходному файлу:");
            String filePath = isReader.readLine();
            BufferedReader fileReader = new BufferedReader(new FileReader(filePath));
            System.out.println("Введите подстроку для стирания:");
            String toErase = isReader.readLine();
            String line;
            SubstringEraser substringEraser = getSubstringEraser(dllPath);
            List<String> strings = new ArrayList<>();
            while (true) {
                line = fileReader.readLine();
                if (line == null)
                    break;
                strings.add(substringEraser.eraseAll(line, toErase));
            }
            System.out.println("Введите путь к файлу для записи:");
            filePath = isReader.readLine();
            FileWriter writer = new FileWriter(filePath);
            strings.forEach(s -> {
                try {
                    writer.write(s + '\n');
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });
            writer.close();
            strings.forEach(System.out::println);
            isReader.close();
        } catch (Throwable e) {
            System.err.println("Ошибка!!!");
            e.printStackTrace();
        }
    }

    private static SubstringEraser getSubstringEraser(String dllPath) {
        AsmFunctions asmFunctions = new AsmFunctions(dllPath);
        return new AwesomeSubstringEraser(asmFunctions);
    }

    private static String getDllPath() {
        String applicationRoot = System.getProperty(USER_DIR);
        return applicationRoot + DLL_RELATIVE_PATH;
    }

    private static void printTitle() {
        System.out.println(TITLE);
    }
}
