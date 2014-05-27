<?hh // strict
namespace Fastuc\Web;

class Inspector implements \Fastuc\Db\QueryListener, \Fastuc\Http\RequestListener
{
	// Time
	private int $beginTime;
	private int $endTime;

	// Memory
	private int $beginMemory;
	private int $endMemory;

	// Database
	private array $queries;

	// Http
	private $httpRequests;

	public function start() : void
	{
		$this->beginTime = microtime( true );

		$this->beginMemory = memory_get_usage();

		$this->queries = array();
		$this->httpRequests = array();
	}

	public function stop() : void
	{
		$this->endTime = microtime( true );

		$this->endMemory = memory_get_usage();
	}

	public function renderHtml() : void
	{
		$inspectorCss = 'cursor: hand; border: 1px solid black; background-color: white; padding: 4px; position: absolute; right: 10px; top: 200px; width: 400px; height: 400px; overflow: scroll;';
		$inspectorJs = 'var p = window.open( \'\', \'a\', \'width=800, height=480\' ); p.document.write( this.innerHTML ); p.document.title = \'Fastuc Web Inspector\'; p.focus(); this.parentNode.removeChild( this );';

		printf( '<div class="FastucWebInspector" style="%s" onclick="%s">', $inspectorCss, $inspectorJs );
		$this->renderTimer();
		$this->renderMemoryUsage();
		$this->renderHttpRequests();
		$this->renderQueries();
		$this->renderServerVars();
		$this->renderFiles();
		echo '</div>';
	}

	private function renderQueries() : void
	{
		if( empty( $this->queries ) )
		{
			return;
		}

		$this->renderTitle( 'Database queries' );

		echo '<ul>';
		foreach( $this->queries as $query )
		{
			printf( '<li>%s</li>', nl2br( $query ) );
		}
		echo '</ul>';
	}

	private function renderHttpRequests() : void
	{
		if( empty( $this->httpRequests ) )
		{
			return;
		}

		$this->renderTitle( 'Http requests' );

		echo '<ul>';
		foreach( $this->httpRequests as $httpRequest )
		{
			printf( '<li>%s</li>', $httpRequest );
		}
		echo '</ul>';
	}

	private function renderServerVars() : void
	{
		$this->renderTitle( 'Server vars' );

		echo '<ul>';
		foreach( $_SERVER as $key => $value )
		{
			printf( '<li><strong>%s</strong>: %s</li>', $key, var_export( $value, true ) );
		}
		echo '</ul>';
	}

	private function renderTimer() : void
	{
		$this->renderTitle( 'Timer' );

		$deltaTime = $this->endTime - $this->beginTime;

		echo <<<HTML
<dl>
	<dt>Begin time</dt><dd>$this->beginTime</dd>
	<dt>End time</dt><dd>$this->endTime</dd>
	<dt>Delta time</dt><dd>$deltaTime</dd>
</dl>
HTML;
	}

	private function renderMemoryUsage() : void
	{
		$this->renderTitle( 'Memory usage' );

		$deltaMemory = $this->endMemory - $this->beginMemory;
		$deltaMemory /= 1024;

		echo <<<HTML
<dl>
	<dt>Begin memory</dt><dd>$this->beginMemory</dd>
	<dt>End memory</dt><dd>$this->endMemory</dd>
	<dt>Delta memory</dt><dd>$deltaMemory</dd>
</dl>
HTML;
	}

	private function renderFiles() : void
	{
		$this->renderTitle( 'Required files' );

		echo '<ul>';
		foreach( get_included_files() as $incFile )
		{
			printf( '<li>%s</li>', $incFile );
		}
		echo '</ul>';
	}

	private function renderTitle( string $title ) : void
	{
		printf( '<h4>%s</h4>', $title );
	}

	public function onPrepareQuery( string $query ) : void
	{
		$this->queries[] = $query;
	}

	public function onHttpRequest( string $url ) : void
	{
		$this->httpRequests[] = $url;
	}
}

