namespace TextReplaceCopy
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_SrcPath = new System.Windows.Forms.TextBox();
            this.textBox_TargetPath = new System.Windows.Forms.TextBox();
            this.textBox_ReplaceList = new System.Windows.Forms.TextBox();
            this.button_FileCopy = new System.Windows.Forms.Button();
            this.button_SendClipboard_VarCode = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.button_SendClipboard_ActionCode = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Src Dir";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 75);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "Target Dir";
            // 
            // textBox_SrcPath
            // 
            this.textBox_SrcPath.Location = new System.Drawing.Point(23, 41);
            this.textBox_SrcPath.Name = "textBox_SrcPath";
            this.textBox_SrcPath.Size = new System.Drawing.Size(483, 19);
            this.textBox_SrcPath.TabIndex = 1;
            // 
            // textBox_TargetPath
            // 
            this.textBox_TargetPath.Location = new System.Drawing.Point(23, 90);
            this.textBox_TargetPath.Name = "textBox_TargetPath";
            this.textBox_TargetPath.Size = new System.Drawing.Size(483, 19);
            this.textBox_TargetPath.TabIndex = 2;
            // 
            // textBox_ReplaceList
            // 
            this.textBox_ReplaceList.AcceptsReturn = true;
            this.textBox_ReplaceList.AcceptsTab = true;
            this.textBox_ReplaceList.Location = new System.Drawing.Point(23, 135);
            this.textBox_ReplaceList.Multiline = true;
            this.textBox_ReplaceList.Name = "textBox_ReplaceList";
            this.textBox_ReplaceList.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox_ReplaceList.Size = new System.Drawing.Size(296, 102);
            this.textBox_ReplaceList.TabIndex = 3;
            // 
            // button_FileCopy
            // 
            this.button_FileCopy.Location = new System.Drawing.Point(431, 214);
            this.button_FileCopy.Name = "button_FileCopy";
            this.button_FileCopy.Size = new System.Drawing.Size(75, 23);
            this.button_FileCopy.TabIndex = 4;
            this.button_FileCopy.Text = "FileCopy";
            this.button_FileCopy.UseVisualStyleBackColor = true;
            this.button_FileCopy.Click += new System.EventHandler(this.button_Copy_Click);
            // 
            // button_SendClipboard_VarCode
            // 
            this.button_SendClipboard_VarCode.Location = new System.Drawing.Point(23, 282);
            this.button_SendClipboard_VarCode.Name = "button_SendClipboard_VarCode";
            this.button_SendClipboard_VarCode.Size = new System.Drawing.Size(122, 39);
            this.button_SendClipboard_VarCode.TabIndex = 5;
            this.button_SendClipboard_VarCode.Text = "SendClipboard";
            this.button_SendClipboard_VarCode.UseVisualStyleBackColor = true;
            this.button_SendClipboard_VarCode.Click += new System.EventHandler(this.button_SendClipboard_VarCode_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(21, 267);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "vars.h";
            // 
            // button_SendClipboard_ActionCode
            // 
            this.button_SendClipboard_ActionCode.Location = new System.Drawing.Point(197, 282);
            this.button_SendClipboard_ActionCode.Name = "button_SendClipboard_ActionCode";
            this.button_SendClipboard_ActionCode.Size = new System.Drawing.Size(122, 39);
            this.button_SendClipboard_ActionCode.TabIndex = 5;
            this.button_SendClipboard_ActionCode.Text = "SendClipboard";
            this.button_SendClipboard_ActionCode.UseVisualStyleBackColor = true;
            this.button_SendClipboard_ActionCode.Click += new System.EventHandler(this.button_SendClipboard_ActionCode_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(195, 267);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(50, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "actions.h";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(553, 353);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button_SendClipboard_ActionCode);
            this.Controls.Add(this.button_SendClipboard_VarCode);
            this.Controls.Add(this.button_FileCopy);
            this.Controls.Add(this.textBox_ReplaceList);
            this.Controls.Add(this.textBox_TargetPath);
            this.Controls.Add(this.textBox_SrcPath);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Text Replace And Copy";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_SrcPath;
        private System.Windows.Forms.TextBox textBox_TargetPath;
        private System.Windows.Forms.TextBox textBox_ReplaceList;
        private System.Windows.Forms.Button button_FileCopy;
        private System.Windows.Forms.Button button_SendClipboard_VarCode;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button_SendClipboard_ActionCode;
        private System.Windows.Forms.Label label4;
    }
}

