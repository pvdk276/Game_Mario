using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mario_BinaryTree
{
    class BinaryTree
    {
        float widthOfCamera;

        //private int id = 1;

        public Node rootNode;

        public List<string> chuoi = new List<string>();

        public BinaryTree(float PositionX, float PositionY, float Width, float Height, float WidthCamera)
        {
            rootNode = new Node("00", PositionX, PositionY, Width, Height);
            widthOfCamera = WidthCamera;
        }

        public void Build(Node node)
        {
            //check if node is large enough
            if (node.width <= widthOfCamera) return;

            //check if node has object
            if (node.listObject.Count == 0) return;

            node.nodeL = new Node(node.id + "00", node.positionX, node.positionY, node.width / 2, node.height);
            node.nodeR = new Node(node.id + "01", node.positionX + node.width / 2, node.positionY, node.width / 2, node.height);
            
            foreach (GameObject gameObject in node.listObject)
            {
                if (node.nodeL.KiemTraThuoc(gameObject))
                {
                    node.nodeL.listObject.Add(gameObject);
                }

                if (node.nodeR.KiemTraThuoc(gameObject))
                {
                    node.nodeR.listObject.Add(gameObject);
                }
            }

            node.listObject.Clear();

            Build(node.nodeL);
            Build(node.nodeR);
        }

        public void BinaryTreeText(Node node)
        {
            chuoi.Add(node.XuatChuoi());

            if (node.nodeL != null) BinaryTreeText(node.nodeL);
            if (node.nodeR != null) BinaryTreeText(node.nodeR);
        }

        public void GhiFileBinaryTree(string FilePath)
        {
            BinaryTreeText(rootNode);
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(FilePath))
            {
                //string line = node.XuatChuoi();
                foreach (string line in chuoi)
                {
                    file.WriteLine(line);
                }

            }
        }
    }
}
