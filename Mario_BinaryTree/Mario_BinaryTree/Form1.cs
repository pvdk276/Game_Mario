using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Mario_BinaryTree
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                String filePath = txbFilePath.Text;
                int numberOfColumns = Int32.Parse(txbNumberOfColumns.Text);
                int numberOfRows = Int32.Parse(txbNumberOfRows.Text);

                int[,] mt = FileUtils.GetInstance().LoadMatrix(filePath, numberOfRows, numberOfColumns);

                BinaryTree tree = new BinaryTree(0, numberOfRows * 50, numberOfColumns * 50, numberOfRows * 50, 750);
                String binaryTreeTextPath = @"C:\Users\ntthi\Downloads\Map_Mario\map1_BinaryTree.txt";
                tree.rootNode.listObject = FileUtils.GetInstance().CreateObjectListFile(mt, numberOfRows, numberOfColumns);

                using (System.IO.StreamWriter sw = System.IO.File.AppendText(@"C:\Users\ntthi\Downloads\Map_Mario\map1_ListObject.txt"))
                {
                    foreach (GameObject gameObject in tree.rootNode.listObject)
                    {
                        sw.WriteLine(gameObject.ToString());
                    }
                }

                tree.Build(tree.rootNode);
                tree.GhiFileBinaryTree(binaryTreeTextPath);
            }
            catch (Exception ex)
            {

            }
            
        }
    }
}
