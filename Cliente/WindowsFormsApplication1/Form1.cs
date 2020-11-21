using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        int puerto = 9600;
        Socket server;
        Thread atender;
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

           
        }

        private void AtenderServidor ()
        {
            while (true)
            {
                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                string [] trozos = Encoding.ASCII.GetString(msg2).Split('/');
                int codigo = Convert.ToInt32 (trozos[0]);
                string mensaje = trozos[1].Split('\0')[0];
                switch (codigo)
                {
                    case 1: 
                        MessageBox.Show("La longitud de tu nombre es: " + mensaje);
                        break;

                    case 2:
                        if (mensaje == "SI")
                            MessageBox.Show("Tu nombre ES bonito.");
                        else
                            MessageBox.Show("Tu nombre NO bonito. Lo siento.");
                        break;

                    case 3:
                        MessageBox.Show(mensaje);
                        break;

                    case 4:
                        if (mensaje == "SI")
                            MessageBox.Show("Tu nombre es palíndromo.");
                        else
                            MessageBox.Show("Tu nombre no es palindromo.");
                        break;

                    case 5:
                        MessageBox.Show(mensaje);
                        break;
                    case 6:
                        label1.Text = mensaje;
                        break;
                }
            }
        }
   
        private void button2_Click(object sender, EventArgs e)
        {
            if (Longitud.Checked)
            {
                string mensaje = "1/" + nombre.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }

            else if (Bonito.Checked)
            {
                string mensaje = "2/" + nombre.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }
            
            else if (altura.Checked)
            {
                string mensaje = "3/" + nombre.Text + "/" + alturaBox.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }

            else if (Palindromo.Checked)
            {
                string mensaje = "4/" + nombre.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }

            else if (mayusculas.Checked)
            {
                string mensaje = "5/" + nombre.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }
        }
            


        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text == "Conectar")
            {

                //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
                //al que deseamos conectarnos
                IPAddress direc = IPAddress.Parse("192.168.56.101");
                IPEndPoint ipep = new IPEndPoint(direc, puerto);

                //Creamos el socket 
                server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                try
                {
                    server.Connect(ipep);//Intentamos conectar el socket
                    this.BackColor = Color.Green;
                    button1.Text = "Desconectar";
                }

                catch (SocketException ex)
                {
                    //Si hay excepcion imprimimos error y salimos del programa con return 
                    MessageBox.Show("No he podido conectar con el servidor");
                    return;
                }
                ThreadStart ts = delegate { AtenderServidor(); };
                atender = new Thread(ts);
                atender.Start();
              
            }

            else
            {
                string mensaje = "0/a";

                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                // Se terminó el servicio. 
                // Nos desconectamos
                atender.Abort();
                this.BackColor = Color.Gray;
                server.Shutdown(SocketShutdown.Both);
                server.Close();
                button1.Text = "Conectar";
            }


        }

        
    }
}
