<?hh // strict
namespace Fastuc\Input;

class Server extends \Fastuc\Utils\TypedArray
{
	public function __construct()
	{
		parent::__construct();

		$this->params = &$_SERVER;
	}

	/**
	 * @return bool
	 */
	public function hasHttpReferer() : bool
	{
		return $this->hasParam( 'HTTP_REFERER' );
	}

	/**
	 * @return string|null
	 */
	public function getHttpReferer() : string
	{
		return $this->hasHttpReferer() ? urldecode( $this->getParam( 'HTTP_REFERER' ) ) : null;
	}

	/**
	 * @return string
	 */
	public function getSearchEngineKeywords() : string
	{
		if( !$this->hasHttpReferer() )
			return null;

		$httpReferer = $this->getHttpReferer();
		$searchEngine = null;
		$keywords = array();

		$paramSeparator = preg_match( '/(\?q=|\?qt=|\?p=)/', $httpReferer) ? '\?' : '\&';
		// Google
		if( preg_match('/www\.google/', $httpReferer ) )
		{
			preg_match('#{$paramSeparator}q=(.*?)\&#si', $httpReferer, $keywords);
			$searchEngine = 'Google';
		}
		// Yahoo
		else if( preg_match('/(yahoo\.com|search\.yahoo)/', $httpReferer ) )
		{
			preg_match('#{$paramSeparator}p=(.*?)\&#si', $httpReferer, $keywords);
			$searchEngine = 'Yahoo';
		}
		// MSN
		else if( preg_match('/search\.msn/', $httpReferer ) )
		{
			preg_match('#{$paramSeparator}q=(.*?)\&#si', $httpReferer, $keywords);
			$searchEngine = 'MSN';
		}
		// AllTheWeb
		else if( preg_match('/www\.alltheweb/', $httpReferer ) )
		{
			preg_match('#{$paramSeparator}q=(.*?)\&#si', $httpReferer, $keywords);
			$searchEngine = 'AllTheWeb';
		}
		// Looksmart
		else if( preg_match('/(looksmart\.com|search\.looksmart)/', $httpReferer ) )
		{
			preg_match('#{$paramSeparator}qt=(.*?)\&#si', $httpReferer, $keywords);
			$searchEngine = 'Looksmart';
		}
		// AskJeeves
		else if( preg_match('/(askjeeves\.com|ask\.com)/', $httpReferer ) )
		{
			preg_match('#{$paramSeparator}q=(.*?)\&#si', $httpReferer, $keywords);
			$searchEngine = 'AskJeeves';
		}

		return array(
			'searchEngine' => $searchEngine,
			'keywords' => $keywords,
			'httpReferer' => $httpReferer
		);
	}
}

