namespace Handle.Test
{
    partial class fHandleTest
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.disposingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.createAndExplictlyDestroyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.createWithoutExplictDestroyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.runGarbageCollectorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.createToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.referenceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.derefrenceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.exhaustAllHandlesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.testListenerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.disposingToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(674, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // disposingToolStripMenuItem
            // 
            this.disposingToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.createAndExplictlyDestroyToolStripMenuItem,
            this.createWithoutExplictDestroyToolStripMenuItem,
            this.toolStripSeparator1,
            this.runGarbageCollectorToolStripMenuItem,
            this.createToolStripMenuItem,
            this.toolStripSeparator2,
            this.exhaustAllHandlesToolStripMenuItem,
            this.toolStripSeparator3,
            this.testListenerToolStripMenuItem});
            this.disposingToolStripMenuItem.Name = "disposingToolStripMenuItem";
            this.disposingToolStripMenuItem.Size = new System.Drawing.Size(71, 20);
            this.disposingToolStripMenuItem.Text = "Disposing";
            // 
            // createAndExplictlyDestroyToolStripMenuItem
            // 
            this.createAndExplictlyDestroyToolStripMenuItem.Name = "createAndExplictlyDestroyToolStripMenuItem";
            this.createAndExplictlyDestroyToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.createAndExplictlyDestroyToolStripMenuItem.Text = "Create and Explictly Destroy";
            this.createAndExplictlyDestroyToolStripMenuItem.Click += new System.EventHandler(this.createAndExplictlyDestroyToolStripMenuItem_Click);
            // 
            // createWithoutExplictDestroyToolStripMenuItem
            // 
            this.createWithoutExplictDestroyToolStripMenuItem.Name = "createWithoutExplictDestroyToolStripMenuItem";
            this.createWithoutExplictDestroyToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.createWithoutExplictDestroyToolStripMenuItem.Text = "Create Without Explict Destroy";
            this.createWithoutExplictDestroyToolStripMenuItem.Click += new System.EventHandler(this.createWithoutExplictDestroyToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(231, 6);
            // 
            // runGarbageCollectorToolStripMenuItem
            // 
            this.runGarbageCollectorToolStripMenuItem.Name = "runGarbageCollectorToolStripMenuItem";
            this.runGarbageCollectorToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.runGarbageCollectorToolStripMenuItem.Text = "Run Garbage Collector";
            this.runGarbageCollectorToolStripMenuItem.Click += new System.EventHandler(this.runGarbageCollectorToolStripMenuItem_Click);
            // 
            // createToolStripMenuItem
            // 
            this.createToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.referenceToolStripMenuItem,
            this.derefrenceToolStripMenuItem});
            this.createToolStripMenuItem.Name = "createToolStripMenuItem";
            this.createToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.createToolStripMenuItem.Text = "Create";
            // 
            // referenceToolStripMenuItem
            // 
            this.referenceToolStripMenuItem.Name = "referenceToolStripMenuItem";
            this.referenceToolStripMenuItem.Size = new System.Drawing.Size(131, 22);
            this.referenceToolStripMenuItem.Text = "Reference";
            this.referenceToolStripMenuItem.Click += new System.EventHandler(this.referenceToolStripMenuItem_Click);
            // 
            // derefrenceToolStripMenuItem
            // 
            this.derefrenceToolStripMenuItem.Name = "derefrenceToolStripMenuItem";
            this.derefrenceToolStripMenuItem.Size = new System.Drawing.Size(131, 22);
            this.derefrenceToolStripMenuItem.Text = "Derefrence";
            this.derefrenceToolStripMenuItem.Click += new System.EventHandler(this.derefrenceToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(231, 6);
            // 
            // exhaustAllHandlesToolStripMenuItem
            // 
            this.exhaustAllHandlesToolStripMenuItem.Name = "exhaustAllHandlesToolStripMenuItem";
            this.exhaustAllHandlesToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.exhaustAllHandlesToolStripMenuItem.Text = "Exhaust All Handles";
            this.exhaustAllHandlesToolStripMenuItem.Click += new System.EventHandler(this.exhaustAllHandlesToolStripMenuItem_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtOutput.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtOutput.Location = new System.Drawing.Point(0, 24);
            this.txtOutput.MaxLength = 0;
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.ReadOnly = true;
            this.txtOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtOutput.Size = new System.Drawing.Size(674, 272);
            this.txtOutput.TabIndex = 2;
            this.txtOutput.WordWrap = false;
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(231, 6);
            // 
            // testListenerToolStripMenuItem
            // 
            this.testListenerToolStripMenuItem.Name = "testListenerToolStripMenuItem";
            this.testListenerToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.testListenerToolStripMenuItem.Text = "Test Listener";
            this.testListenerToolStripMenuItem.Click += new System.EventHandler(this.testListenerToolStripMenuItem_Click);
            // 
            // fHandleTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(674, 296);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "fHandleTest";
            this.Text = "libusbK Handles Example";
            this.Load += new System.EventHandler(this.fHandleTest_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.fHandleTest_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem disposingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem createAndExplictlyDestroyToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem runGarbageCollectorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem createWithoutExplictDestroyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem createToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem referenceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem derefrenceToolStripMenuItem;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem exhaustAllHandlesToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem testListenerToolStripMenuItem;
    }
}

