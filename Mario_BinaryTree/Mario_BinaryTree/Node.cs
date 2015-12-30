using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mario_BinaryTree
{
    class Node
    {
        public string id;
        public float positionX; //toa do cua dinh top-left
        public float positionY;
        public float width;
        public float height;

        public Node nodeL;
        public Node nodeR;

        public List<GameObject> listObject;

        public Node()
        {
            id = "";
            positionX = 0;
            positionY = 0;
            width = 0;
            height = 0;

            nodeL = null;
            nodeR = null;

            listObject = new List<GameObject>();
        }

        public Node(string id, float positionX, float positionY, float width, float height)
        {
            this.id = id;
            this.positionX = positionX;
            this.positionY = positionY;
            this.width = width;
            this.height = height;

            nodeL = null;
            nodeR = null;

            listObject = new List<GameObject>();
        }

        public Boolean KiemTraThuoc(GameObject gameObject)
        {
            //4 position of gameObject
            float tlPositionX = gameObject.posX - gameObject.width / 2;
            float tlPositionY = gameObject.posY + gameObject.height / 2;

            float trPositionX = gameObject.posX + gameObject.width / 2;
            float trPositionY = gameObject.posY + gameObject.height / 2;

            float blPositionX = gameObject.posX - gameObject.width / 2;
            float blPositionY = gameObject.posY - gameObject.height / 2;

            float brPositionX = gameObject.posX + gameObject.width / 2;
            float brPositionY = gameObject.posY - gameObject.height / 2;

            if (tlPositionX >= positionX && tlPositionX <= positionX + width)
            {
                if (tlPositionY <= positionY && tlPositionY >= positionY - height)
                {
                    return true;
                }
            }

            if (trPositionX >= positionX && trPositionX <= positionX + width)
            {
                if (trPositionY <= positionY && trPositionY >= positionY - height)
                {
                    return true;
                }
            }

            if (blPositionX >= positionX && blPositionX <= positionX + width)
            {
                if (blPositionY <= positionY && blPositionY >= positionY - height)
                {
                    return true;
                }
            }

            if (brPositionX >= positionX && brPositionX <= positionX + width)
            {
                if (brPositionY <= positionY && brPositionY >= positionY - height)
                {
                    return true;
                }
            }

            if (tlPositionY <= positionY && tlPositionY >= positionY - height)
            {
                if (positionX >= tlPositionX && positionX <= trPositionX)
                {
                    return true;
                }
            }

            if (blPositionY <= positionY && blPositionY >= positionY - height)
            {
                if (positionX >= tlPositionX && positionX <= trPositionX)
                {
                    return true;
                }
            }

            return false;
        }

        public string XuatChuoi()
        {
            string str = "";
            str += id + '\t' + positionX.ToString() + '\t' + positionY.ToString() + '\t' + width.ToString() + '\t' + height.ToString();
            foreach (GameObject gameObject in listObject)
            {
                str += '\t' + gameObject.id.ToString();
            }
            return str;
        }
    }
}
