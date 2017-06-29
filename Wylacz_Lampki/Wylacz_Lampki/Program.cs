using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Wylacz_Lampki
{
    class Program
    {
        // Metoda losuj musi byc zaimplementowana przez wywolywanie toggle()
        // bo istnieja ulozenia w ktorych zadanie jest nierozwiazywalne
        static public void losuj(bool[,] tabl)
        {
            var ilosc = new Random();
            int numberOfToggle = tabl.Length;
            int losWys, losSzer;

            while (numberOfToggle > 0)
            {
                losWys = ilosc.Next(1, tabl.GetLength(0) + 1);
                losSzer = ilosc.Next(1, tabl.GetLength(1) + 1);

                toggle(tabl, losWys - 1, losSzer - 1);
                numberOfToggle--;
            }

            if (sprawdz(tabl))
            {
                toggle(tabl, 0, 0);
                toggle(tabl, 0, 1);
            }
        }
        static public void wyswietlTablice(bool[,] tabl, ConsoleColor kolor)
        {
            Console.BackgroundColor = ConsoleColor.DarkGray;
            Console.ForegroundColor = kolor;

            for (int iter1 = 0; iter1 < tabl.GetLength(0); iter1++)
            {
                for (int iter2 = 0; iter2 < tabl.GetLength(1); iter2++)

                    Console.Write(tabl[iter1, iter2] ? '█' : ' ');
                Console.WriteLine();
            }

            Console.ResetColor();
        }
        static public void toggle(bool[,] tabl, int wiersz, int kolumna)
        {
            tabl[wiersz, kolumna] = !tabl[wiersz, kolumna];
            if (wiersz > 0) tabl[wiersz - 1, kolumna] = !tabl[wiersz - 1, kolumna];        // gorny
            if (wiersz < tabl.GetLength(0) - 1) tabl[wiersz + 1, kolumna] = !tabl[wiersz + 1, kolumna];          //dolny
            if (kolumna > 0) tabl[wiersz, kolumna - 1] = !tabl[wiersz, kolumna - 1];             // lewy
            if (kolumna < tabl.GetLength(1) - 1) tabl[wiersz, kolumna + 1] = !tabl[wiersz, kolumna + 1];        //prawy 
        }
        static public bool sprawdz(bool[,] tabl)
        {
            for (int iter1 = 0; iter1 < tabl.GetLength(0); iter1++)
                for (int iter2 = 0; iter2 < tabl.GetLength(1); iter2++)
                    if (tabl[iter1, iter2])
                        return false;

            return true;
        }
        static public bool wygrana(bool[,] tabl)
        {
            if (sprawdz(tabl))                             // jesli wygrales
            {
                Console.Clear();
                wyswietlTablice(tabl, ConsoleColor.Yellow);

                Console.ForegroundColor = ConsoleColor.Green;
                Console.Write("ZWYCIESTWO :)");
                Console.ReadKey();
                return true;
            }
            return false;
        }

        static public void przetestujPozostaleWiersze(bool[,] tablOper, bool[,] tablAktualRozw, int wysokosc, int szerokosc)
        {

            if (tablOper[0, szerokosc - 1])
                obslPole(tablOper, tablAktualRozw, 1, szerokosc - 1, true);

            for (int it = 2; it < wysokosc; it++)
                for (int it2 = 0; it2 < szerokosc; it2++)
                    if (tablOper[it - 1, it2])
                        obslPole(tablOper, tablAktualRozw, it, it2, true);

        }

        static public void CofnijPrzetestujPozostaleWiersze(bool[,] tablOper, bool[,] tablAktualRozw, int wysokosc, int szerokosc)
        {

            if (tablAktualRozw[1, szerokosc - 1])
                obslPole(tablOper, tablAktualRozw, 1, szerokosc - 1, false);

            for (int it = 2; it < wysokosc; it++)
                for (int it2 = 0; it2 < szerokosc; it2++)
                    if (tablAktualRozw[it, it2])
                        obslPole(tablOper, tablAktualRozw, it, it2, false);

        }

        static public void obslPole(bool[,] tablOper, bool[,] tablAktualRozw, int wys, int szer, bool flaga)
        {

            toggle(tablOper, wys, szer);
            tablAktualRozw[wys, szer] = flaga;
        }

        static public void oneCombination(bool[,] tablOper, bool[,] tablAktualRozw, bool[,] tablRozw, int kolumna, params int[] wspolrzedne)
        {
            int dlugosc = (wspolrzedne.Length / 2) * 2; // ignorujemy nadmierny nieparzysty parametr

            for (int iter = 0; iter < dlugosc; iter += 2)
                obslPole(tablOper, tablAktualRozw, wspolrzedne[iter], wspolrzedne[iter + 1], true);

            podpowiedz(tablOper, tablAktualRozw, tablRozw, kolumna + 1);

            for (int iter = 0; iter < dlugosc; iter += 2)
                obslPole(tablOper, tablAktualRozw, wspolrzedne[iter], wspolrzedne[iter + 1], false);

        }

        static public void podpowiedz(bool[,] tablOper, bool[,] tablAktualRozw, bool[,] tablRozw, int kolumna = 0)
        {
            int wysokosc = tablOper.GetLength(0);
            int szerokosc = tablOper.GetLength(1);

            if (kolumna < szerokosc - 1)
            {
                if (kolumna == 0)
                {
                    if (tablOper[0, 0])
                    {
                        oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 0, 0);
                        oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 0, 0, 0, 1, 1, 0);
                    }
                    else
                    {
                        oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 0, 0, 1, 0);
                        oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 0, 0, 0, 1);
                    }

                }
                if (tablOper[0, kolumna] == true)
                {
                    oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 0, kolumna + 1);
                    oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 1, kolumna);
                }
                else
                {
                    oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna, 0, kolumna + 1, 1, kolumna);
                    oneCombination(tablOper, tablAktualRozw, tablRozw, kolumna);
                }


            }
            else
            {

                przetestujPozostaleWiersze(tablOper, tablAktualRozw, wysokosc, szerokosc);

                if (sprawdz(tablOper))          // Rozwiazan moze byc wiecej niz jeden
                    Array.Copy(tablAktualRozw, tablRozw, tablAktualRozw.Length);

                CofnijPrzetestujPozostaleWiersze(tablOper, tablAktualRozw, wysokosc, szerokosc);
            }

        }

        static void Main()
        {
            string pomoc;
            bool podpowiadam = false;
            int n, wiersz = 0, kolumna = 0;

            Console.Write(" Wielkosc tablicy : ");

            if (!int.TryParse(Console.ReadLine(), out n) || n <= 1 || n > 11)             // sprawdz czy liczba
                n = 3;                                                                   // i wczytaj wielkosc tablicy

            var tabl = new bool[n, n];
            var tablAktualRozw = new bool[n, n];
            var tablRozw = new bool[n, n];

            losuj(tabl);

            do
            {
                Console.Clear();

                podpowiedz(tabl, tablAktualRozw, tablRozw);

                if (podpowiadam)
                    wyswietlTablice(tablRozw, ConsoleColor.Red);
                Console.WriteLine();
                wyswietlTablice(tabl, ConsoleColor.Yellow);

                Console.Write("Rzad (od 1) : ");                                               // wprowadz rzad
                if (!int.TryParse(pomoc = Console.ReadLine(), out wiersz) || wiersz < 1 || wiersz > n)
                {
                    podpowiadam |= pomoc == "ratuj";
                    continue;
                }

                Console.Write("Kolumna (od 1) : ");                                             // wprowadz kolumne
                if (!int.TryParse(pomoc = Console.ReadLine(), out kolumna) || kolumna < 1 || kolumna > n)
                {
                    podpowiadam |= pomoc == "ratuj";
                    continue;
                }

                toggle(tabl, wiersz - 1, kolumna - 1);                            // zapal lampki

            } while (!wygrana(tabl));
        }
    }
}
