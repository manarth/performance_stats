(function() {

  (function($) {
    var PerformanceStats;
    PerformanceStats = (function() {

      function PerformanceStats(chart_element, chart_info) {
        var attr, val, _ref;
        this.chart_element = chart_element;
        this.chart_info = chart_info;
        this.options = {
          'title': this.chart_info.title,
          'width': 500,
          'height': 300
        };
        if (this.chart_info.options != null) {
          _ref = this.chart_info.options;
          for (attr in _ref) {
            val = _ref[attr];
            this.options[attr] = val;
          }
        }
        this.data = new google.visualization.DataTable();
        this.addColumns(this.chart_info.columns);
        this.addRows(this.chart_info.data);
      }

      PerformanceStats.prototype.addColumns = function(columns) {
        var key, value, _results;
        _results = [];
        for (key in columns) {
          value = columns[key];
          _results.push(this.data.addColumn(key, value));
        }
        return _results;
      };

      PerformanceStats.prototype.addRows = function(data) {
        var key, value;
        return this.data.addRows((function() {
          var _results;
          _results = [];
          for (key in data) {
            value = data[key];
            _results.push([key, value]);
          }
          return _results;
        })());
      };

      PerformanceStats.prototype.render = function(el) {
        var chart;
        switch (this.chart_info.type) {
          case 'pie':
            chart = new google.visualization.PieChart(el);
            break;
          case 'column':
            chart = new google.visualization.ColumnChart(el);
            break;
          case 'bar':
            chart = new google.visualization.BarChart(el);
        }
        this.chart_element.append(el);
        return chart.draw(this.data, this.options);
      };

      return PerformanceStats;

    })();
    google.load('visualization', '1.0', {
      'packages': ['corechart']
    });
    return google.setOnLoadCallback(function() {
      var chart, chart_info, charts_div, el, i, _ref, _results;
      charts_div = $('#charts');
      _ref = Drupal.settings.performance_stats;
      _results = [];
      for (i in _ref) {
        chart_info = _ref[i];
        el = $("<div id='#chart-" + i + "' class='performance_chart'></div>")[0];
        chart = new PerformanceStats(charts_div, chart_info);
        _results.push(chart.render(el));
      }
      return _results;
    });
  })(jQuery);

}).call(this);
