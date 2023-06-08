using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_11
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            SqlConnection conn = new SqlConnection("Data Source=LAPTOP-LA4CMMH4\\SQLEXPRESS;Initial Catalog=lab11;Integrated Security=True"); //Connection String
            conn.Open();
            MessageBox.Show("Connection Open");
            SqlCommand cm;
            string un = textBox1.Text;
            string pass = textBox2.Text;
            string query = "Insert into Users (username, password) values ('" + un + "','" + pass + "')";
            cm = new SqlCommand(query, conn);
            cm.ExecuteNonQuery();
            cm.Dispose();
            conn.Close();
            MessageBox.Show("success");

        }
    }
}
