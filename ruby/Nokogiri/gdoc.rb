require "google_drive"

# Logs in.
# You can also use OAuth. See document of
# GoogleDrive.login_with_oauth for details.
session = GoogleDrive.login(ENV['GMAIL_ACCOUNT'],ENV['GMAIL_APP_PASSWORD'])

ws = session.spreadsheet_by_key("1oouesgudvxX3wbKzK_66MNM2Zo0jvyxNT5Xn3rtWoXY").worksheets[0]

num= ws.num_rows + 1 

date = DateTime.now.strftime('%F')

ws[num,1] = num-1
ws[num,2] = "kalaexj" 
ws[num,3] = "test #{num}" 
ws[num,4] = date 
ws.save()

# Dumps all cells.
for col in 1..ws.num_cols
    p ws[num, col]
end

# Reloads the worksheet to get changes by other clients.
#ws.reload()
