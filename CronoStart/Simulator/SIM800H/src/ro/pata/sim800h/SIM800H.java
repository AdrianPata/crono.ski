/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ro.pata.sim800h;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.DefaultListModel;
import javax.swing.ListModel;

/**
 *
 * @author MPLAB
 */
public class SIM800H extends javax.swing.JFrame {

    ComTool comTool;
    DefaultListModel modelRX;
    DefaultListModel modelTX;
    
    
    /**
     * Creates new form SIM800H
     */
    public SIM800H() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        btnSend = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        lstRX = new javax.swing.JList<>();
        jScrollPane2 = new javax.swing.JScrollPane();
        lstTX = new javax.swing.JList<>();
        btmClear = new javax.swing.JButton();
        btnTest = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
            public void windowOpened(java.awt.event.WindowEvent evt) {
                formWindowOpened(evt);
            }
        });

        btnSend.setText("Send");
        btnSend.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSendActionPerformed(evt);
            }
        });

        lstRX.setModel(new javax.swing.AbstractListModel<String>() {
            String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
            public int getSize() { return strings.length; }
            public String getElementAt(int i) { return strings[i]; }
        });
        jScrollPane1.setViewportView(lstRX);

        lstTX.setModel(new javax.swing.AbstractListModel<String>() {
            String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
            public int getSize() { return strings.length; }
            public String getElementAt(int i) { return strings[i]; }
        });
        jScrollPane2.setViewportView(lstTX);

        btmClear.setText("Clear");
        btmClear.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btmClearActionPerformed(evt);
            }
        });

        btnTest.setText("Disconnect");
        btnTest.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnTestActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(0, 435, Short.MAX_VALUE)
                        .addComponent(btnTest)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(btmClear)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(btnSend))
                    .addComponent(jScrollPane1)
                    .addComponent(jScrollPane2))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 432, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 109, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnSend)
                    .addComponent(btmClear)
                    .addComponent(btnTest))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnSendActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSendActionPerformed
        try {
            String c=(String) modelTX.getElementAt(lstTX.getSelectedIndex());
            comTool.Send(c.getBytes());
        } catch (IOException ex) {
            Logger.getLogger(SIM800H.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_btnSendActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        comTool.disconnect();
    }//GEN-LAST:event_formWindowClosing

    private void formWindowOpened(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowOpened
        modelRX=new DefaultListModel();
        modelTX=new DefaultListModel();
        
        modelTX.addElement("OK");
        modelTX.addElement("+CPIN: SIM PIN");
        modelTX.addElement("+CPIN: READY");
        modelTX.addElement("+CREG: 1,\"00AA\",\"54BB\"");
        
        lstTX.setModel(modelTX);
        lstRX.setModel(modelRX);
        
        try{
            comTool=new ComTool(modelRX);
            comTool.Connect();
        } catch (Exception ex){
            ex.printStackTrace();
        }
    }//GEN-LAST:event_formWindowOpened

    private void btmClearActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btmClearActionPerformed
        modelRX.clear();
    }//GEN-LAST:event_btmClearActionPerformed

    private void btnTestActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnTestActionPerformed
        comTool.disconnect();
    }//GEN-LAST:event_btnTestActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(SIM800H.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(SIM800H.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(SIM800H.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(SIM800H.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new SIM800H().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btmClear;
    private javax.swing.JButton btnSend;
    private javax.swing.JButton btnTest;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JList<String> lstRX;
    private javax.swing.JList<String> lstTX;
    // End of variables declaration//GEN-END:variables
}
