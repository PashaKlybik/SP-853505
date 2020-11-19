using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Laba2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text == "")
                MessageBox.Show("Заполните TextBox");
            else 
                listBox1.Items.Add(textBox1.Text);

        }
        private void button2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox2.Items.Clear();
        }

        private void button3_Click(object sender, EventArgs e)
        {
         
            listBox2.Items.Add(listBox1.SelectedItem);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox1.Items.RemoveAt(listBox1.SelectedIndex);
            listBox2.Items.RemoveAt(listBox2.SelectedIndex);
        }

    }
}
