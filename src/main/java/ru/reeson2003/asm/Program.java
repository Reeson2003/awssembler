package ru.reeson2003.asm;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Date: 27.05.2018.
 * Time: 18:51.
 *
 * @author Pavel Gavrilov.
 */
public class Program implements Title{
    public static void main(String[] args) {
        try {
            System.out.println(TITLE);
            BufferedReader isReader = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Введите путь к исходному файлу:");
            String filePath = isReader.readLine();
            BufferedReader fileReader = new BufferedReader(new FileReader(filePath));
            System.out.println("Введите подстроку для стирания:");
            String toErase = isReader.readLine();
            String line;
            SubstringEraser substringEraser = new AwesomeSubstringEraser();
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
        }
    }
}
