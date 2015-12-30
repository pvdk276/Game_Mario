using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mario_BinaryTree
{
    class GameObject
    {
        public int id;
        public int typeId;
        public float posX;
        public float posY;
        public float width;
        public float height;

        public GameObject(int id, int typeId, float posX, float posY, float width, float height)
        {
            this.id = id;
            this.typeId = typeId;
            this.posX = posX;
            this.posY = posY;
            this.width = width;
            this.height = height;
        }

        public override String ToString()
        {
            return (id + "\t" + typeId + "\t" + posX + "\t" + posY + "\t" + width + "\t" + height);
        }
    }
}
