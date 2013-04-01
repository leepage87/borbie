package borbiemapeditor;

import java.awt.Frame;
import javax.swing.JDialog;

/**
 *
 * @author richard
 */
public class PreferencesPanel extends JDialog {
    
    
    public static final int PREF_WIDTH = 480;
    public static final int PREF_HEIGHT = 360;
    
    
    // CONSTRUCTOR: create the JDialog pane centered above the main window,
    //  and populate it with all of the preferences values.
    public PreferencesPanel(Frame parent) {
        super(parent);
        
        // set size, and lock resizability
        this.setResizable(false);
        this.setSize(PreferencesPanel.PREF_WIDTH, PreferencesPanel.PREF_HEIGHT);
        
        this.setTitle("Preferences - Borbie Map Editor");
        
        // set location on screen centered above parent (mainWindow frame)
        int parentX = parent.getLocationOnScreen().x;
        int parentY = parent.getLocationOnScreen().y;
        int parentW = parent.getWidth();
        int parentH = parent.getHeight();
        int locX = (parentX + (parentW / 2)) - (PreferencesPanel.PREF_WIDTH / 2);
        int locY = (parentY + (parentH / 2)) - (PreferencesPanel.PREF_HEIGHT / 2);
        this.setLocation(locX, locY);
        
        this.setVisible(true);
    }
}
