using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace OSI_LAB_7
{
    class Program
    {
        static void Main(string[] args)
        {
            int l = -1;
            while (l != 0)
            {
                Console.WriteLine("Введите необходимый пункт: ");
                Console.WriteLine("1 - генерация ЭЦП");
                Console.WriteLine("0 - выход");
                l = int.Parse(Console.ReadLine());
                Console.Clear();
                switch (l)
                {
                    case 1:
                        {
                            Console.WriteLine("Введите текст для шифрования: ");
                            string text = Console.ReadLine();
                            byte[] HashValue = GetHash(text);

                            byte[] SignedHashValue1;

                            RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();


                            RSAParameters rSA = new RSAParameters();
                            rSA = RSA.ExportParameters(true);

                            Console.WriteLine(rSA.Modulus.GetValue(0).ToString() + rSA.Modulus.GetValue(1).ToString() + rSA.Modulus.GetValue(2).ToString() + rSA.Modulus.GetValue(3).ToString()); 
                            Console.WriteLine(rSA.Exponent.GetValue(0).ToString() + rSA.Exponent.GetValue(1).ToString() + rSA.Exponent.GetValue(2).ToString());
                            Console.WriteLine(rSA.D.GetValue(0).ToString()+ rSA.D.GetValue(1).ToString() + rSA.D.GetValue(2).ToString() + rSA.D.GetValue(3).ToString());


                            //RSA.ImportParameters(rSAParameters);

                            RSAPKCS1SignatureFormatter RSAFormatter = new RSAPKCS1SignatureFormatter(RSA);
                            RSAPKCS1SignatureDeformatter RSADeformatter = new RSAPKCS1SignatureDeformatter(RSA);

                            RSAFormatter.SetHashAlgorithm("MD5");
                            RSADeformatter.SetHashAlgorithm("MD5");
                            RSADeformatter.SetKey(RSA);

                            SignedHashValue1 = RSAFormatter.CreateSignature(HashValue);

                            Console.Write("Хеш-образ: "); Console.WriteLine(Convert.ToBase64String(HashValue));
                            Console.Write("Сообщение для 2-го человека (исходное сообщение; ЭЦП): "); Console.WriteLine("("+text+";"+ Convert.ToBase64String(SignedHashValue1) + ")");
                            byte[] HashValue2 = GetHash(Convert.ToBase64String(SignedHashValue1));

                            if (RSADeformatter.VerifySignature(HashValue, SignedHashValue1))
                            {
                                Console.WriteLine("Подпись верна.");
                            }
                            else
                            {
                                Console.WriteLine("Подпись неверна.");
                            }
                            break;
                        }
                    default: break;
                }
            }
        }

      
        public static byte[] GetHash(string input)
        {
            var md5 = MD5.Create();
            var hash = md5.ComputeHash(Encoding.UTF8.GetBytes(input));

            return hash;
        }
    }

    

}
