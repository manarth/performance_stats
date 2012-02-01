(($) ->
  class PerformanceStats
    constructor: (@chart_element, @chart_info) ->
      @options = {
        'title': @chart_info.title,
        'width': 500,
        'height': 300
      }

      # Merge passed options into defaults.
      if @chart_info.options?
        @options[attr] = val for attr, val of @chart_info.options

      @data = new google.visualization.DataTable()
      @addColumns @chart_info.columns
      @addRows @chart_info.data

    addColumns: (columns) ->
      for key, value of columns
        @data.addColumn(key, value)

    addRows: (data) ->
      @data.addRows ([key, value] for key, value of data)

    render: (el) ->
      switch @chart_info.type
        when 'pie'
          chart = new google.visualization.PieChart(el)
        when 'column'
          chart = new google.visualization.ColumnChart(el)
        when 'bar'
          chart = new google.visualization.BarChart(el)

      @chart_element.append(el)
      chart.draw(@data, @options)


  # Load the Visualization API and the piechart package.
  google.load('visualization', '1.0', {'packages':['corechart']})

  # Set a callback to run when the Google Visualization API is loaded.
  google.setOnLoadCallback( ->
    charts_div = $('#charts')
    for i, chart_info of Drupal.settings.performance_stats
      el = $("<div id='#chart-#{i}' class='performance_chart'></div>")[0]
      chart = new PerformanceStats charts_div, chart_info
      chart.render el
  )
)(jQuery)
