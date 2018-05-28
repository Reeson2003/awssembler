package ru.reeson2003.asm;

import java.io.*;

/**
 * Date: 27.05.2018.
 * Time: 18:51.
 *
 * @author Pavel Gavrilov.
 */
public class Program implements Title{
    public static void main(String[] args) {
        try {
            printTitle();
            SubstringEraser substringEraser = getSubstringEraser();
            BufferedReader isReader = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Введите путь к исходному файлу:");
            String filePath = isReader.readLine();
            BufferedReader fileReader = new BufferedReader(new FileReader(filePath));
            System.out.println("Введите подстроку для стирания:");
            String toErase = isReader.readLine();
            System.out.println("Введите путь к файлу для записи:");
            filePath = isReader.readLine();
            FileWriter writer = new FileWriter(filePath);
            String line;
            while (true) {
                line = fileReader.readLine();
                if (line == null)
                    break;
                String erased = substringEraser.eraseAll(line, toErase) + '\n';
                writer.write(erased);
                System.out.println(erased);
            }
            writer.close();
            fileReader.close();
            isReader.close();
        } catch (Throwable e) {
            System.err.println("Ошибка!!!");
            e.printStackTrace();
        }
    }

    private static SubstringEraser getSubstringEraser() {
        System.out.println(System.getProperty("java.library.path"));
        AsmFunctions asmFunctions = new AsmFunctions("awssembler");
        return new AwesomeSubstringEraser(asmFunctions);
    }

    private static void printTitle() {
        System.out.println(TITLE);
    }
}
