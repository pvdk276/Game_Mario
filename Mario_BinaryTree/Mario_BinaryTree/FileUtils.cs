using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mario_BinaryTree
{
    class FileUtils
    {
        public static FileUtils instance;

        public static FileUtils GetInstance()
        {
            if (instance == null) instance = new FileUtils();
            return instance;
        }

        public int[,] LoadMatrix(String filePath, int m, int n)
        {
            int[,] mt = new int[m,n];
            int i = 0, j = 0;
            String[] lines = System.IO.File.ReadAllLines(filePath);

            foreach(String line in lines)
            {
                String[] items = line.Split(',');
                for(j = 0; j < items.Length; j++)
                {
                    if (items[j].Equals("")) continue;
                    mt[i, j] = Int32.Parse(items[j]);
                }
                i++;
            }

            return mt;
        }

        public List<GameObject> CreateObjectListFile(int[,] mt, int m, int n)
        {
            List<GameObject> list = new List<GameObject>();
            float tileWidth = 50;
            float tileHeight = 50;
            int id = 0;

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    switch (mt[i, j])
                    {
                        case 3:
                            id++;
                            int typeId = 1;
                            float width = 50;
                            float height = 50;
                            float x = (j * tileWidth) + (width / 2);
                            float y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 4:
                            id++;
                            typeId = 2;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 5:
                            id++;
                            typeId = 3;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 112:
                            id++;
                            typeId = 4;
                            width = 150;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 7:
                            id++;
                            typeId = 5;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 59:
                            id++;
                            typeId = 6;
                            width = 100;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 62:
                            id++;
                            typeId = 7;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 218:
                            id++;
                            typeId = 8;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 221:
                            id++;
                            typeId = 9;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 222:
                            id++;
                            typeId = 10;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 223:
                            id++;
                            typeId = 11;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 115:
                            id++;
                            typeId = 12;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 147:
                            id++;
                            typeId = 13;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 42:
                            id++;
                            typeId = 14;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 61:
                            id++;
                            typeId = 15;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 169:
                            id++;
                            typeId = 16;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 6:
                            id++;
                            typeId = 17;
                            width = 50;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 69:
                            id++;
                            typeId = 18;
                            width = 200;
                            height = 32;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 224:
                            id++;
                            typeId = 19;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 225:
                            id++;
                            typeId = 20;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 226:
                            id++;
                            typeId = 21;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                        case 227:
                            id++;
                            typeId = 22;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;
                    }
                }
            }
            return list;
        }
    }
}
