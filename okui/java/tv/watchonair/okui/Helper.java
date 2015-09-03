package tv.watchonair.okui;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Handler;

import java.lang.Runnable;
import java.lang.String;

public class Helper {
    private Activity _activity;
    
    public Helper(Activity activity) {
        _activity = activity;
    }
    
    static public class OpenDialogCallback {
        public native void invoke(int button);
        private long _nativeHandle = 0;
    }
    
    public void openDialog(final String title, final String message, final String[] buttons, final OpenDialogCallback callback) {
        Handler mainHandler = new Handler(_activity.getMainLooper());
        Runnable runnable = new Runnable() {
            @Override 
            public void run() {
                AlertDialog.Builder builder = new AlertDialog.Builder(_activity);
                builder.setCancelable(false);
                if (buttons.length > 2) {
                    builder.setTitle(message);
                    builder.setItems(buttons, new DialogInterface.OnClickListener() {
                        @Override 
                        public void onClick(DialogInterface dialog, int which) {
                            callback.invoke(which);
                        }
                    });
                } else {
                    builder.setTitle(title);
                    builder.setMessage(message);
                    builder.setPositiveButton(buttons[0], new DialogInterface.OnClickListener() {
                        @Override 
                        public void onClick(DialogInterface dialog, int which) {
                            callback.invoke(0);
                        }
                    });
                    if (buttons.length > 1) {
                        builder.setNegativeButton(buttons[1], new DialogInterface.OnClickListener() {
                            @Override 
                            public void onClick(DialogInterface dialog, int which) {
                                callback.invoke(1);
                            }
                        });
                    }
                }
                builder.show();
            }
        };
        mainHandler.post(runnable);
    }
}