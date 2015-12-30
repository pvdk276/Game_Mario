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
                        case 3: //left-land
                            id++;
                            int typeId = 1;
                            float width = 50;
                            float height = 50;
                            float x = (j * tileWidth) + (width / 2);
                            float y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 4: //center-land
                            id++;
                            typeId = 2;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 5: //right-land
                            id++;
                            typeId = 3;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 6: //jump
                            id++;
                            typeId = 4;
                            width = 50;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 7: //pipe
                            id++;
                            typeId = 5;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 39: //tank
                            id++;
                            typeId = 6;
                            width = 100;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            //y = (m - i) * tileHeight - (height / 2);
                            y = (m - i) * tileHeight;

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 42: //stone
                            id++;
                            typeId = 7;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 59: //grass
                            id++;
                            typeId = 8;
                            width = 100;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 61: //carnivorous
                            id++;
                            typeId = 9;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 62: //brick
                            id++;
                            typeId = 10;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 109: //left-pipe
                            id++;
                            typeId = 11;
                            width = 150;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 75: //left-pipe-1
                            id++;
                            typeId = 12;
                            width = 150;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 78: //left-pipe-2
                            id++;
                            typeId = 13;
                            width = 150;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 112: //cloud
                            id++;
                            typeId = 14;
                            width = 150;
                            height = 100;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 115: //carnivorous-pipe
                            id++;
                            typeId = 15;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 145: //down-pipe
                            id++;
                            typeId = 16;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 147: //down-pipe-1
                            id++;
                            typeId = 17;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 149: //down-pipe-2
                            id++;
                            typeId = 18;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 169: //up-pipe-1
                            id++;
                            typeId = 19;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 55: //up-pipe-2
                            id++;
                            typeId = 20;
                            width = 100;
                            height = 150;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 63: //tower
                            id++;
                            typeId = 21;
                            width = 300;
                            height = 400;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 15: //down-bar
                            id++;
                            typeId = 22;
                            width = 200;
                            height = 32;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 33: //up-bar
                            id++;
                            typeId = 23;
                            width = 200;
                            height = 32;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 51: //right-bar
                            id++;
                            typeId = 24;
                            width = 200;
                            height = 32;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 69: //bar
                            id++;
                            typeId = 25;
                            width = 200;
                            height = 32;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 87: //coin
                            id++;
                            typeId = 26;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 88: //coin-block
                            id++;
                            typeId = 27;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 89: //coin-brick
                            id++;
                            typeId = 28;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 105: //flower-block
                            id++;
                            typeId = 29;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 106: //green-mushroom-block
                            id++;
                            typeId = 30;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 107: //red-mushroom-block
                            id++;
                            typeId = 31;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 123: //star-block
                            id++;
                            typeId = 32;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 124: //enemy
                            id++;
                            typeId = 33;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 125: //wing-turtle
                            id++;
                            typeId = 34;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 142: //turtle
                            id++;
                            typeId = 35;
                            width = 50;
                            height = 50;
                            x = (j * tileWidth) + (width / 2);
                            y = (m - i) * tileHeight - (height / 2);

                            list.Add(new GameObject(id, typeId, x, y, width, height));

                            break;

                        case 143: //fire-turtle
                            id++;
                            typeId = 36;
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
